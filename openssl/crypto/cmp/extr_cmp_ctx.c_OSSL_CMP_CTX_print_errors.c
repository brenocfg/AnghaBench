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
struct TYPE_3__ {int /*<<< orphan*/ * log_cb; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_CMP_print_errors_cb (int /*<<< orphan*/ *) ; 

void OSSL_CMP_CTX_print_errors(OSSL_CMP_CTX *ctx)
{
    OSSL_CMP_print_errors_cb(ctx == NULL ? NULL : ctx->log_cb);
}