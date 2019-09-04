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
struct TYPE_6__ {TYPE_1__* cipher; } ;
struct TYPE_5__ {int (* ctrl ) (TYPE_2__*,int,int,void*) ;} ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_CTX_CTRL ; 
 int /*<<< orphan*/  EVP_R_CTRL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVP_R_CTRL_OPERATION_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int,int,void*) ; 

int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr)
{
    int ret;

    if (!ctx->cipher) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_NO_CIPHER_SET);
        return 0;
    }

    if (!ctx->cipher->ctrl) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_CTRL_NOT_IMPLEMENTED);
        return 0;
    }

    ret = ctx->cipher->ctrl(ctx, type, arg, ptr);
    if (ret == -1) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL,
               EVP_R_CTRL_OPERATION_NOT_IMPLEMENTED);
        return 0;
    }
    return ret;
}