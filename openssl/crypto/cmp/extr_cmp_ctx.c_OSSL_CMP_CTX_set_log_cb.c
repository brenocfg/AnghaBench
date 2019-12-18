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
struct TYPE_4__ {int /*<<< orphan*/  log_cb; } ;
typedef  int /*<<< orphan*/  OSSL_cmp_log_cb_t ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_TRACE_CATEGORY_CMP ; 
 int /*<<< orphan*/  OSSL_trace_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_cmp_log_trace_cb ; 

int OSSL_CMP_CTX_set_log_cb(OSSL_CMP_CTX *ctx, OSSL_cmp_log_cb_t cb)
{
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    ctx->log_cb = cb;

#ifndef OPENSSL_NO_TRACE
    /* do also in case cb == NULL, to switch off logging output: */
    if (!OSSL_trace_set_callback(OSSL_TRACE_CATEGORY_CMP,
                                 ossl_cmp_log_trace_cb, ctx))
        return 0;
#endif

    return 1;
}