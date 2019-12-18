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
struct TYPE_4__ {int error; int (* verify_cb ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ X509_STORE_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int verify_cb_crl(X509_STORE_CTX *ctx, int err)
{
    ctx->error = err;
    return ctx->verify_cb(0, ctx);
}