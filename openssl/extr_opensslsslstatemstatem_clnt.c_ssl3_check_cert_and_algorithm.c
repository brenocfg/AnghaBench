#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* new_cipher; } ;
struct TYPE_14__ {int /*<<< orphan*/ * peer_tmp; TYPE_2__ tmp; } ;
struct TYPE_16__ {TYPE_4__ s3; TYPE_3__* session; } ;
struct TYPE_15__ {long amask; } ;
struct TYPE_13__ {int /*<<< orphan*/  peer; } ;
struct TYPE_11__ {long algorithm_mkey; long algorithm_auth; } ;
typedef  TYPE_5__ SSL_CERT_LOOKUP ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM ; 
 size_t SSL_PKEY_RSA ; 
 int /*<<< orphan*/  SSL_R_BAD_ECC_CERT ; 
 int /*<<< orphan*/  SSL_R_MISSING_RSA_ENCRYPTING_CERT ; 
 int /*<<< orphan*/  SSL_R_MISSING_SIGNING_CERT ; 
 long SSL_aCERT ; 
 int SSL_aECDSA ; 
 long SSL_kDHE ; 
 long SSL_kRSA ; 
 long SSL_kRSAPSK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get0_pubkey (int /*<<< orphan*/ ) ; 
 TYPE_5__* ssl_cert_lookup_by_pkey (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ ssl_check_srvr_ecc_cert_and_alg (int /*<<< orphan*/ ,TYPE_6__*) ; 

int ssl3_check_cert_and_algorithm(SSL *s)
{
    const SSL_CERT_LOOKUP *clu;
    size_t idx;
    long alg_k, alg_a;

    alg_k = s->s3.tmp.new_cipher->algorithm_mkey;
    alg_a = s->s3.tmp.new_cipher->algorithm_auth;

    /* we don't have a certificate */
    if (!(alg_a & SSL_aCERT))
        return 1;

    /* This is the passed certificate */
    clu = ssl_cert_lookup_by_pkey(X509_get0_pubkey(s->session->peer), &idx);

    /* Check certificate is recognised and suitable for cipher */
    if (clu == NULL || (alg_a & clu->amask) == 0) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                 SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM,
                 SSL_R_MISSING_SIGNING_CERT);
        return 0;
    }

#ifndef OPENSSL_NO_EC
    if (clu->amask & SSL_aECDSA) {
        if (ssl_check_srvr_ecc_cert_and_alg(s->session->peer, s))
            return 1;
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                 SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM, SSL_R_BAD_ECC_CERT);
        return 0;
    }
#endif
#ifndef OPENSSL_NO_RSA
    if (alg_k & (SSL_kRSA | SSL_kRSAPSK) && idx != SSL_PKEY_RSA) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                 SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM,
                 SSL_R_MISSING_RSA_ENCRYPTING_CERT);
        return 0;
    }
#endif
#ifndef OPENSSL_NO_DH
    if ((alg_k & SSL_kDHE) && (s->s3.peer_tmp == NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
#endif

    return 1;
}