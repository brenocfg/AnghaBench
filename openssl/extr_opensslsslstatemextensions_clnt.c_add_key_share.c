#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {int /*<<< orphan*/ * pkey; } ;
struct TYPE_8__ {unsigned int group_id; TYPE_1__ tmp; } ;
struct TYPE_9__ {scalar_t__ hello_retry_request; TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 size_t EVP_PKEY_get1_tls_encodedpoint (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_ADD_KEY_SHARE ; 
 scalar_t__ SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/ * ssl_generate_pkey_group (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static int add_key_share(SSL *s, WPACKET *pkt, unsigned int curve_id)
{
    unsigned char *encoded_point = NULL;
    EVP_PKEY *key_share_key = NULL;
    size_t encodedlen;

    if (s->s3.tmp.pkey != NULL) {
        if (!ossl_assert(s->hello_retry_request == SSL_HRR_PENDING)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_ADD_KEY_SHARE,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        /*
         * Could happen if we got an HRR that wasn't requesting a new key_share
         */
        key_share_key = s->s3.tmp.pkey;
    } else {
        key_share_key = ssl_generate_pkey_group(s, curve_id);
        if (key_share_key == NULL) {
            /* SSLfatal() already called */
            return 0;
        }
    }

    /* Encode the public key. */
    encodedlen = EVP_PKEY_get1_tls_encodedpoint(key_share_key,
                                                &encoded_point);
    if (encodedlen == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_ADD_KEY_SHARE, ERR_R_EC_LIB);
        goto err;
    }

    /* Create KeyShareEntry */
    if (!WPACKET_put_bytes_u16(pkt, curve_id)
            || !WPACKET_sub_memcpy_u16(pkt, encoded_point, encodedlen)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_ADD_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    /*
     * TODO(TLS1.3): When changing to send more than one key_share we're
     * going to need to be able to save more than one EVP_PKEY. For now
     * we reuse the existing tmp.pkey
     */
    s->s3.tmp.pkey = key_share_key;
    s->s3.group_id = curve_id;
    OPENSSL_free(encoded_point);

    return 1;
 err:
    if (s->s3.tmp.pkey == NULL)
        EVP_PKEY_free(key_share_key);
    OPENSSL_free(encoded_point);
    return 0;
}