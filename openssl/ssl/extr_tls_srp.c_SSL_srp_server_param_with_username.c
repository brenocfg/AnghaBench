#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  b ;
struct TYPE_5__ {int (* TLS_ext_srp_username_callback ) (TYPE_2__*,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * v; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; int /*<<< orphan*/  b; int /*<<< orphan*/ * B; int /*<<< orphan*/ * s; int /*<<< orphan*/  SRP_cb_arg; } ;
struct TYPE_6__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 scalar_t__ RAND_priv_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/ * SRP_Calc_B (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL3_AL_FATAL ; 
 int SSL_AD_INTERNAL_ERROR ; 
 int SSL_AD_UNKNOWN_PSK_IDENTITY ; 
 int SSL_ERROR_NONE ; 
 int SSL_MAX_MASTER_KEY_LENGTH ; 
 int stub1 (TYPE_2__*,int*,int /*<<< orphan*/ ) ; 

int SSL_srp_server_param_with_username(SSL *s, int *ad)
{
    unsigned char b[SSL_MAX_MASTER_KEY_LENGTH];
    int al;

    *ad = SSL_AD_UNKNOWN_PSK_IDENTITY;
    if ((s->srp_ctx.TLS_ext_srp_username_callback != NULL) &&
        ((al =
          s->srp_ctx.TLS_ext_srp_username_callback(s, ad,
                                                   s->srp_ctx.SRP_cb_arg)) !=
         SSL_ERROR_NONE))
        return al;

    *ad = SSL_AD_INTERNAL_ERROR;
    if ((s->srp_ctx.N == NULL) ||
        (s->srp_ctx.g == NULL) ||
        (s->srp_ctx.s == NULL) || (s->srp_ctx.v == NULL))
        return SSL3_AL_FATAL;

    if (RAND_priv_bytes(b, sizeof(b)) <= 0)
        return SSL3_AL_FATAL;
    s->srp_ctx.b = BN_bin2bn(b, sizeof(b), NULL);
    OPENSSL_cleanse(b, sizeof(b));

    /* Calculate:  B = (kv + g^b) % N  */

    return ((s->srp_ctx.B =
             SRP_Calc_B(s->srp_ctx.b, s->srp_ctx.N, s->srp_ctx.g,
                        s->srp_ctx.v)) !=
            NULL) ? SSL_ERROR_NONE : SSL3_AL_FATAL;
}