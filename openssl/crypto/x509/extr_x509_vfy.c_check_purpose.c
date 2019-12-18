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
struct TYPE_6__ {int num_untrusted; TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {int purpose; int flags; int /*<<< orphan*/  trust; } ;

/* Variables and functions */
 int /*<<< orphan*/  X509_TRUST_NO_SS_COMPAT ; 
#define  X509_TRUST_REJECTED 129 
#define  X509_TRUST_TRUSTED 128 
 int X509_TRUST_UNTRUSTED ; 
 int /*<<< orphan*/  X509_V_ERR_INVALID_PURPOSE ; 
 int X509_V_FLAG_X509_STRICT ; 
 int /*<<< orphan*/  X509_check_purpose (int /*<<< orphan*/ *,int,int) ; 
 int X509_check_trust (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_cb_cert (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_purpose(X509_STORE_CTX *ctx, X509 *x, int purpose, int depth,
                         int must_be_ca)
{
    int tr_ok = X509_TRUST_UNTRUSTED;

    /*
     * For trusted certificates we want to see whether any auxiliary trust
     * settings trump the purpose constraints.
     *
     * This is complicated by the fact that the trust ordinals in
     * ctx->param->trust are entirely independent of the purpose ordinals in
     * ctx->param->purpose!
     *
     * What connects them is their mutual initialization via calls from
     * X509_STORE_CTX_set_default() into X509_VERIFY_PARAM_lookup() which sets
     * related values of both param->trust and param->purpose.  It is however
     * typically possible to infer associated trust values from a purpose value
     * via the X509_PURPOSE API.
     *
     * Therefore, we can only check for trust overrides when the purpose we're
     * checking is the same as ctx->param->purpose and ctx->param->trust is
     * also set.
     */
    if (depth >= ctx->num_untrusted && purpose == ctx->param->purpose)
        tr_ok = X509_check_trust(x, ctx->param->trust, X509_TRUST_NO_SS_COMPAT);

    switch (tr_ok) {
    case X509_TRUST_TRUSTED:
        return 1;
    case X509_TRUST_REJECTED:
        break;
    default:
        switch (X509_check_purpose(x, purpose, must_be_ca > 0)) {
        case 1:
            return 1;
        case 0:
            break;
        default:
            if ((ctx->param->flags & X509_V_FLAG_X509_STRICT) == 0)
                return 1;
        }
        break;
    }

    return verify_cb_cert(ctx, x, depth, X509_V_ERR_INVALID_PURPOSE);
}