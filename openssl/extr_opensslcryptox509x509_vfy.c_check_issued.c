#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int X509_V_ERR_PATH_LOOP ; 
 int X509_V_OK ; 
 int X509_check_issued (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cert_self_signed (int /*<<< orphan*/ *) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_issued(X509_STORE_CTX *ctx, X509 *x, X509 *issuer)
{
    int ret;
    if (x == issuer)
        return cert_self_signed(x);
    ret = X509_check_issued(issuer, x);
    if (ret == X509_V_OK) {
        int i;
        X509 *ch;
        /* Special case: single self signed certificate */
        if (cert_self_signed(x) && sk_X509_num(ctx->chain) == 1)
            return 1;
        for (i = 0; i < sk_X509_num(ctx->chain); i++) {
            ch = sk_X509_value(ctx->chain, i);
            if (ch == issuer || !X509_cmp(ch, issuer)) {
                ret = X509_V_ERR_PATH_LOOP;
                break;
            }
        }
    }

    return (ret == X509_V_OK);
}