#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_9__ {int /*<<< orphan*/ * pkey; } ;
struct TYPE_10__ {unsigned int group_id; int /*<<< orphan*/ * peer_tmp; TYPE_1__ tmp; } ;
struct TYPE_11__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_tls_encodedpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 unsigned int SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_R_BAD_ECPOINT ; 
 int /*<<< orphan*/  SSL_R_BAD_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_SECOP_CURVE_SUPPORTED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_derive (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_3__*,unsigned int const**,size_t*) ; 
 int /*<<< orphan*/  tls_group_allowed (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_key_share(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                             size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned int group_id;
    PACKET encoded_pt;
    EVP_PKEY *ckey = s->s3.tmp.pkey, *skey = NULL;

    /* Sanity check */
    if (ckey == NULL || s->s3.peer_tmp != NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (!PACKET_get_net_2(pkt, &group_id)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    if ((context & SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST) != 0) {
        const uint16_t *pgroups = NULL;
        size_t i, num_groups;

        if (PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                     SSL_R_LENGTH_MISMATCH);
            return 0;
        }

        /*
         * It is an error if the HelloRetryRequest wants a key_share that we
         * already sent in the first ClientHello
         */
        if (group_id == s->s3.group_id) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PARSE_STOC_KEY_SHARE, SSL_R_BAD_KEY_SHARE);
            return 0;
        }

        /* Validate the selected group is one we support */
        tls1_get_supported_groups(s, &pgroups, &num_groups);
        for (i = 0; i < num_groups; i++) {
            if (group_id == pgroups[i])
                break;
        }
        if (i >= num_groups
                || !tls_group_allowed(s, group_id, SSL_SECOP_CURVE_SUPPORTED)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PARSE_STOC_KEY_SHARE, SSL_R_BAD_KEY_SHARE);
            return 0;
        }

        s->s3.group_id = group_id;
        EVP_PKEY_free(s->s3.tmp.pkey);
        s->s3.tmp.pkey = NULL;
        return 1;
    }

    if (group_id != s->s3.group_id) {
        /*
         * This isn't for the group that we sent in the original
         * key_share!
         */
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 SSL_R_BAD_KEY_SHARE);
        return 0;
    }

    if (!PACKET_as_length_prefixed_2(pkt, &encoded_pt)
            || PACKET_remaining(&encoded_pt) == 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    skey = EVP_PKEY_new();
    if (skey == NULL || EVP_PKEY_copy_parameters(skey, ckey) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (!EVP_PKEY_set1_tls_encodedpoint(skey, PACKET_data(&encoded_pt),
                                        PACKET_remaining(&encoded_pt))) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_KEY_SHARE,
                 SSL_R_BAD_ECPOINT);
        EVP_PKEY_free(skey);
        return 0;
    }

    if (ssl_derive(s, ckey, skey, 1) == 0) {
        /* SSLfatal() already called */
        EVP_PKEY_free(skey);
        return 0;
    }
    s->s3.peer_tmp = skey;
#endif

    return 1;
}