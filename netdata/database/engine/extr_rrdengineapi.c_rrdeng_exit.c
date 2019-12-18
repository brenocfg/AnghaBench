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
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;
struct rrdengine_instance {TYPE_1__ worker_config; } ;
struct rrdeng_cmd {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RRDENG_FD_BUDGET_PER_INSTANCE ; 
 int /*<<< orphan*/  RRDENG_SHUTDOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 struct rrdengine_instance default_global_ctx ; 
 int /*<<< orphan*/  finalize_rrd_files (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  free_page_cache (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  freez (struct rrdengine_instance*) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdeng_enq_cmd (TYPE_1__*,struct rrdeng_cmd*) ; 
 int /*<<< orphan*/  rrdeng_reserved_file_descriptors ; 
 scalar_t__ uv_thread_join (int /*<<< orphan*/ *) ; 

int rrdeng_exit(struct rrdengine_instance *ctx)
{
    struct rrdeng_cmd cmd;

    if (NULL == ctx) {
        return 1;
    }

    /* TODO: add page to page cache */
    cmd.opcode = RRDENG_SHUTDOWN;
    rrdeng_enq_cmd(&ctx->worker_config, &cmd);

    assert(0 == uv_thread_join(&ctx->worker_config.thread));

    finalize_rrd_files(ctx);
    free_page_cache(ctx);

    if (ctx != &default_global_ctx) {
        freez(ctx);
    }
    rrd_stat_atomic_add(&rrdeng_reserved_file_descriptors, -RRDENG_FD_BUDGET_PER_INSTANCE);
    return 0;
}