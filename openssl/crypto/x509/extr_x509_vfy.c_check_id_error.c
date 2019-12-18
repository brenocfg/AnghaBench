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
struct TYPE_4__ {int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ X509_STORE_CTX ;

/* Variables and functions */
 int verify_cb_cert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_id_error(X509_STORE_CTX *ctx, int errcode)
{
    return verify_cb_cert(ctx, ctx->cert, 0, errcode);
}