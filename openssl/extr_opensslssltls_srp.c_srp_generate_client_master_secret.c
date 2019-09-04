#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* (* SRP_give_srp_client_pwd_callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  a; int /*<<< orphan*/  g; int /*<<< orphan*/  B; int /*<<< orphan*/  N; int /*<<< orphan*/  login; int /*<<< orphan*/  s; int /*<<< orphan*/  SRP_cb_arg; int /*<<< orphan*/  A; } ;
struct TYPE_8__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (char*,int /*<<< orphan*/ ) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * SRP_Calc_client_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SRP_Calc_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SRP_Verify_B_mod_N (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SRP_GENERATE_CLIENT_MASTER_SECRET ; 
 int /*<<< orphan*/  SSL_R_CALLBACK_FAILED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_generate_master_secret (TYPE_2__*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int srp_generate_client_master_secret(SSL *s)
{
    BIGNUM *x = NULL, *u = NULL, *K = NULL;
    int ret = -1, tmp_len = 0;
    char *passwd = NULL;
    unsigned char *tmp = NULL;

    /*
     * Checks if b % n == 0
     */
    if (SRP_Verify_B_mod_N(s->srp_ctx.B, s->srp_ctx.N) == 0
            || (u = SRP_Calc_u(s->srp_ctx.A, s->srp_ctx.B, s->srp_ctx.N))
               == NULL
            || s->srp_ctx.SRP_give_srp_client_pwd_callback == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_SRP_GENERATE_CLIENT_MASTER_SECRET, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    if ((passwd = s->srp_ctx.SRP_give_srp_client_pwd_callback(s,
                                                      s->srp_ctx.SRP_cb_arg))
            == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_SRP_GENERATE_CLIENT_MASTER_SECRET,
                 SSL_R_CALLBACK_FAILED);
        goto err;
    }
    if ((x = SRP_Calc_x(s->srp_ctx.s, s->srp_ctx.login, passwd)) == NULL
            || (K = SRP_Calc_client_key(s->srp_ctx.N, s->srp_ctx.B,
                                        s->srp_ctx.g, x,
                                        s->srp_ctx.a, u)) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_SRP_GENERATE_CLIENT_MASTER_SECRET, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    tmp_len = BN_num_bytes(K);
    if ((tmp = OPENSSL_malloc(tmp_len)) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_SRP_GENERATE_CLIENT_MASTER_SECRET, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    BN_bn2bin(K, tmp);
    /* Calls SSLfatal() as required */
    ret = ssl_generate_master_secret(s, tmp, tmp_len, 1);
 err:
    BN_clear_free(K);
    BN_clear_free(x);
    if (passwd != NULL)
        OPENSSL_clear_free(passwd, strlen(passwd));
    BN_clear_free(u);
    return ret;
}