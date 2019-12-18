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
struct TYPE_7__ {int /*<<< orphan*/  login; int /*<<< orphan*/ * A; int /*<<< orphan*/  N; } ;
struct TYPE_9__ {TYPE_2__* session; TYPE_1__ srp_ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/ * srp_username; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CKE_SRP ; 
 int /*<<< orphan*/  SSL_R_BAD_SRP_A_LENGTH ; 
 int /*<<< orphan*/  SSL_R_BAD_SRP_PARAMETERS ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_generate_server_master_secret (TYPE_3__*) ; 

__attribute__((used)) static int tls_process_cke_srp(SSL *s, PACKET *pkt)
{
#ifndef OPENSSL_NO_SRP
    unsigned int i;
    const unsigned char *data;

    if (!PACKET_get_net_2(pkt, &i)
        || !PACKET_get_bytes(pkt, &data, i)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_SRP,
                 SSL_R_BAD_SRP_A_LENGTH);
        return 0;
    }
    if ((s->srp_ctx.A = BN_bin2bn(data, i, NULL)) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_SRP,
                 ERR_R_BN_LIB);
        return 0;
    }
    if (BN_ucmp(s->srp_ctx.A, s->srp_ctx.N) >= 0 || BN_is_zero(s->srp_ctx.A)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PROCESS_CKE_SRP,
                 SSL_R_BAD_SRP_PARAMETERS);
        return 0;
    }
    OPENSSL_free(s->session->srp_username);
    s->session->srp_username = OPENSSL_strdup(s->srp_ctx.login);
    if (s->session->srp_username == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_SRP,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if (!srp_generate_server_master_secret(s)) {
        /* SSLfatal() already called */
        return 0;
    }

    return 1;
#else
    /* Should never happen */
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_SRP,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}