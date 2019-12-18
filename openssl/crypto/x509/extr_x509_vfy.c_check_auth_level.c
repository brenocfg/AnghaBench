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
struct TYPE_8__ {int /*<<< orphan*/  chain; TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {scalar_t__ auth_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  X509_V_ERR_CA_KEY_TOO_SMALL ; 
 int /*<<< orphan*/  X509_V_ERR_CA_MD_TOO_WEAK ; 
 int /*<<< orphan*/  check_key_level (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_sig_level (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ verify_cb_cert (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_auth_level(X509_STORE_CTX *ctx)
{
    int i;
    int num = sk_X509_num(ctx->chain);

    if (ctx->param->auth_level <= 0)
        return 1;

    for (i = 0; i < num; ++i) {
        X509 *cert = sk_X509_value(ctx->chain, i);

        /*
         * We've already checked the security of the leaf key, so here we only
         * check the security of issuer keys.
         */
        if (i > 0 && !check_key_level(ctx, cert) &&
            verify_cb_cert(ctx, cert, i, X509_V_ERR_CA_KEY_TOO_SMALL) == 0)
            return 0;
        /*
         * We also check the signature algorithm security of all certificates
         * except those of the trust anchor at index num-1.
         */
        if (i < num - 1 && !check_sig_level(ctx, cert) &&
            verify_cb_cert(ctx, cert, i, X509_V_ERR_CA_MD_TOO_WEAK) == 0)
            return 0;
    }
    return 1;
}