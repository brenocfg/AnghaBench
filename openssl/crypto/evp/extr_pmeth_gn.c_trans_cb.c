#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* keygen_info; int (* pkey_gencb ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 TYPE_1__* BN_GENCB_get_arg (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int trans_cb(int a, int b, BN_GENCB *gcb)
{
    EVP_PKEY_CTX *ctx = BN_GENCB_get_arg(gcb);
    ctx->keygen_info[0] = a;
    ctx->keygen_info[1] = b;
    return ctx->pkey_gencb(ctx);
}