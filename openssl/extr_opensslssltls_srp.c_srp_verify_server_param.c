#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ strength; scalar_t__ (* SRP_verify_param_callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  N; int /*<<< orphan*/  g; int /*<<< orphan*/  SRP_cb_arg; int /*<<< orphan*/  B; } ;
struct TYPE_6__ {TYPE_2__ srp_ctx; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ SRP_CTX ;

/* Variables and functions */
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_check_known_gN_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INSUFFICIENT_SECURITY ; 
 int /*<<< orphan*/  SSL_F_SRP_VERIFY_SERVER_PARAM ; 
 int /*<<< orphan*/  SSL_R_BAD_DATA ; 
 int /*<<< orphan*/  SSL_R_CALLBACK_FAILED ; 
 int /*<<< orphan*/  SSL_R_INSUFFICIENT_SECURITY ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int srp_verify_server_param(SSL *s)
{
    SRP_CTX *srp = &s->srp_ctx;
    /*
     * Sanity check parameters: we can quickly check B % N == 0 by checking B
     * != 0 since B < N
     */
    if (BN_ucmp(srp->g, srp->N) >= 0 || BN_ucmp(srp->B, srp->N) >= 0
        || BN_is_zero(srp->B)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_SRP_VERIFY_SERVER_PARAM,
                 SSL_R_BAD_DATA);
        return 0;
    }

    if (BN_num_bits(srp->N) < srp->strength) {
        SSLfatal(s, SSL_AD_INSUFFICIENT_SECURITY, SSL_F_SRP_VERIFY_SERVER_PARAM,
                 SSL_R_INSUFFICIENT_SECURITY);
        return 0;
    }

    if (srp->SRP_verify_param_callback) {
        if (srp->SRP_verify_param_callback(s, srp->SRP_cb_arg) <= 0) {
            SSLfatal(s, SSL_AD_INSUFFICIENT_SECURITY,
                     SSL_F_SRP_VERIFY_SERVER_PARAM,
                     SSL_R_CALLBACK_FAILED);
            return 0;
        }
    } else if (!SRP_check_known_gN_param(srp->g, srp->N)) {
        SSLfatal(s, SSL_AD_INSUFFICIENT_SECURITY, SSL_F_SRP_VERIFY_SERVER_PARAM,
                 SSL_R_INSUFFICIENT_SECURITY);
        return 0;
    }

    return 1;
}