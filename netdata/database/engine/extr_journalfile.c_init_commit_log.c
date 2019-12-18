#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int transaction_id; scalar_t__ buf_pos; int /*<<< orphan*/ * buf; } ;
struct rrdengine_instance {TYPE_1__ commit_log; } ;

/* Variables and functions */

void init_commit_log(struct rrdengine_instance *ctx)
{
    ctx->commit_log.buf = NULL;
    ctx->commit_log.buf_pos = 0;
    ctx->commit_log.transaction_id = 1;
}