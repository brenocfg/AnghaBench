#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_10__ {TYPE_2__* new_cipher; } ;
struct TYPE_11__ {TYPE_3__ tmp; } ;
struct TYPE_12__ {scalar_t__ version; TYPE_4__ s3; TYPE_1__* cert; } ;
struct TYPE_9__ {int algorithm_mkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctype_len; scalar_t__ ctype; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_CT_DSS_EPHEMERAL_DH ; 
 int /*<<< orphan*/  SSL3_CT_DSS_SIGN ; 
 int /*<<< orphan*/  SSL3_CT_RSA_EPHEMERAL_DH ; 
 int /*<<< orphan*/  SSL3_CT_RSA_SIGN ; 
 scalar_t__ SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_SECOP_SIGALG_MASK ; 
 int SSL_aDSS ; 
 int SSL_aECDSA ; 
 int SSL_aRSA ; 
 int SSL_kDHE ; 
 int SSL_kGOST ; 
 scalar_t__ TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_CT_ECDSA_SIGN ; 
 int /*<<< orphan*/  TLS_CT_GOST01_SIGN ; 
 int /*<<< orphan*/  TLS_CT_GOST12_512_SIGN ; 
 int /*<<< orphan*/  TLS_CT_GOST12_SIGN ; 
 int WPACKET_memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_set_sig_mask (int*,TYPE_5__*,int /*<<< orphan*/ ) ; 

int ssl3_get_req_cert_type(SSL *s, WPACKET *pkt)
{
    uint32_t alg_k, alg_a = 0;

    /* If we have custom certificate types set, use them */
    if (s->cert->ctype)
        return WPACKET_memcpy(pkt, s->cert->ctype, s->cert->ctype_len);
    /* Get mask of algorithms disabled by signature list */
    ssl_set_sig_mask(&alg_a, s, SSL_SECOP_SIGALG_MASK);

    alg_k = s->s3.tmp.new_cipher->algorithm_mkey;

#ifndef OPENSSL_NO_GOST
    if (s->version >= TLS1_VERSION && (alg_k & SSL_kGOST))
            return WPACKET_put_bytes_u8(pkt, TLS_CT_GOST01_SIGN)
                    && WPACKET_put_bytes_u8(pkt, TLS_CT_GOST12_SIGN)
                    && WPACKET_put_bytes_u8(pkt, TLS_CT_GOST12_512_SIGN);
#endif

    if ((s->version == SSL3_VERSION) && (alg_k & SSL_kDHE)) {
#ifndef OPENSSL_NO_DH
# ifndef OPENSSL_NO_RSA
        if (!WPACKET_put_bytes_u8(pkt, SSL3_CT_RSA_EPHEMERAL_DH))
            return 0;
# endif
# ifndef OPENSSL_NO_DSA
        if (!WPACKET_put_bytes_u8(pkt, SSL3_CT_DSS_EPHEMERAL_DH))
            return 0;
# endif
#endif                          /* !OPENSSL_NO_DH */
    }
#ifndef OPENSSL_NO_RSA
    if (!(alg_a & SSL_aRSA) && !WPACKET_put_bytes_u8(pkt, SSL3_CT_RSA_SIGN))
        return 0;
#endif
#ifndef OPENSSL_NO_DSA
    if (!(alg_a & SSL_aDSS) && !WPACKET_put_bytes_u8(pkt, SSL3_CT_DSS_SIGN))
        return 0;
#endif
#ifndef OPENSSL_NO_EC
    /*
     * ECDSA certs can be used with RSA cipher suites too so we don't
     * need to check for SSL_kECDH or SSL_kECDHE
     */
    if (s->version >= TLS1_VERSION
            && !(alg_a & SSL_aECDSA)
            && !WPACKET_put_bytes_u8(pkt, TLS_CT_ECDSA_SIGN))
        return 0;
#endif
    return 1;
}