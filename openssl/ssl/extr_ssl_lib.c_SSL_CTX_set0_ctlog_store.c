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
struct TYPE_3__ {int /*<<< orphan*/ * ctlog_store; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  int /*<<< orphan*/  CTLOG_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  CTLOG_STORE_free (int /*<<< orphan*/ *) ; 

void SSL_CTX_set0_ctlog_store(SSL_CTX *ctx, CTLOG_STORE * logs)
{
    CTLOG_STORE_free(ctx->ctlog_store);
    ctx->ctlog_store = logs;
}