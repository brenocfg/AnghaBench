#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* meth; } ;
struct TYPE_4__ {int (* ctrl_str ) (int /*<<< orphan*/ ,char const*,char const*) ;} ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_MAC_CTRL_STR ; 
 int /*<<< orphan*/  EVP_R_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 

int EVP_MAC_ctrl_str(EVP_MAC_CTX *ctx, const char *type, const char *value)
{
    int ok = 1;

    if (ctx == NULL || ctx->meth == NULL || ctx->meth->ctrl_str == NULL) {
        EVPerr(EVP_F_EVP_MAC_CTRL_STR, EVP_R_COMMAND_NOT_SUPPORTED);
        return -2;
    }

    ok = ctx->meth->ctrl_str(ctx->data, type, value);

    if (ok == -2)
        EVPerr(EVP_F_EVP_MAC_CTRL_STR, EVP_R_COMMAND_NOT_SUPPORTED);
    return ok;
}