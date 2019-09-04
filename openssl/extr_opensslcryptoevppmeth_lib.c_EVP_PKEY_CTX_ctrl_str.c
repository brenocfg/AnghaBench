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
struct TYPE_7__ {TYPE_1__* pmeth; } ;
struct TYPE_6__ {int (* ctrl_str ) (TYPE_2__*,char const*,char const*) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_CTX_CTRL_STR ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_MD ; 
 int EVP_PKEY_CTX_md (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_TYPE_SIG ; 
 int /*<<< orphan*/  EVP_R_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int stub1 (TYPE_2__*,char const*,char const*) ; 

int EVP_PKEY_CTX_ctrl_str(EVP_PKEY_CTX *ctx,
                          const char *name, const char *value)
{
    if (!ctx || !ctx->pmeth || !ctx->pmeth->ctrl_str) {
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL_STR, EVP_R_COMMAND_NOT_SUPPORTED);
        return -2;
    }
    if (strcmp(name, "digest") == 0)
        return EVP_PKEY_CTX_md(ctx, EVP_PKEY_OP_TYPE_SIG, EVP_PKEY_CTRL_MD,
                               value);
    return ctx->pmeth->ctrl_str(ctx, name, value);
}