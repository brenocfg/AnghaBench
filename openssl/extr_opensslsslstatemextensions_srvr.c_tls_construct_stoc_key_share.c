#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_8__ {int /*<<< orphan*/ * pkey; } ;
struct TYPE_9__ {TYPE_1__ tmp; int /*<<< orphan*/  group_id; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_10__ {scalar_t__ hello_retry_request; TYPE_2__ s3; int /*<<< orphan*/  hit; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 size_t EVP_PKEY_get1_tls_encodedpoint (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE ; 
 scalar_t__ SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_key_share ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ ssl_derive (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ssl_generate_pkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls13_generate_handshake_secret (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_stoc_key_share(SSL *s, WPACKET *pkt,
                                        unsigned int context, X509 *x,
                                        size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned char *encodedPoint;
    size_t encoded_pt_len = 0;
    EVP_PKEY *ckey = s->s3.peer_tmp, *skey = NULL;

    if (s->hello_retry_request == SSL_HRR_PENDING) {
        if (ckey != NULL) {
            /* Original key_share was acceptable so don't ask for another one */
            return EXT_RETURN_NOT_SENT;
        }
        if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_key_share)
                || !WPACKET_start_sub_packet_u16(pkt)
                || !WPACKET_put_bytes_u16(pkt, s->s3.group_id)
                || !WPACKET_close(pkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }

        return EXT_RETURN_SENT;
    }

    if (ckey == NULL) {
        /* No key_share received from client - must be resuming */
        if (!s->hit || !tls13_generate_handshake_secret(s, NULL, 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE, ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        return EXT_RETURN_NOT_SENT;
    }

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_key_share)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_put_bytes_u16(pkt, s->s3.group_id)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    skey = ssl_generate_pkey(ckey);
    if (skey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE,
                 ERR_R_MALLOC_FAILURE);
        return EXT_RETURN_FAIL;
    }

    /* Generate encoding of server key */
    encoded_pt_len = EVP_PKEY_get1_tls_encodedpoint(skey, &encodedPoint);
    if (encoded_pt_len == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE,
                 ERR_R_EC_LIB);
        EVP_PKEY_free(skey);
        return EXT_RETURN_FAIL;
    }

    if (!WPACKET_sub_memcpy_u16(pkt, encodedPoint, encoded_pt_len)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        EVP_PKEY_free(skey);
        OPENSSL_free(encodedPoint);
        return EXT_RETURN_FAIL;
    }
    OPENSSL_free(encodedPoint);

    /* This causes the crypto state to be updated based on the derived keys */
    s->s3.tmp.pkey = skey;
    if (ssl_derive(s, skey, ckey, 1) == 0) {
        /* SSLfatal() already called */
        return EXT_RETURN_FAIL;
    }
    return EXT_RETURN_SENT;
#else
    return EXT_RETURN_FAIL;
#endif
}