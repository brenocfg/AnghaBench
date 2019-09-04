#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_vdpau_ctx {int is_preempted; int preemption_user_notified; double last_preemption_retry_fail; int /*<<< orphan*/  preemption_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_vdpau_ctx*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct mp_vdpau_ctx*,char*) ; 
 int /*<<< orphan*/  mark_vdpau_objects_uninitialized (struct mp_vdpau_ctx*) ; 
 double mp_time_sec () ; 
 scalar_t__ win_x11_init_vdpau_procs (struct mp_vdpau_ctx*,int) ; 

__attribute__((used)) static int handle_preemption(struct mp_vdpau_ctx *ctx)
{
    if (!ctx->is_preempted)
        return 0;
    mark_vdpau_objects_uninitialized(ctx);
    if (!ctx->preemption_user_notified) {
        MP_ERR(ctx, "Got display preemption notice! Will attempt to recover.\n");
        ctx->preemption_user_notified = true;
    }
    /* Trying to initialize seems to be quite slow, so only try once a
     * second to avoid using 100% CPU. */
    if (ctx->last_preemption_retry_fail &&
        mp_time_sec() - ctx->last_preemption_retry_fail < 1.0)
        return -1;
    if (win_x11_init_vdpau_procs(ctx, false) < 0) {
        ctx->last_preemption_retry_fail = mp_time_sec();
        return -1;
    }
    ctx->preemption_user_notified = false;
    ctx->last_preemption_retry_fail = 0;
    ctx->is_preempted = false;
    ctx->preemption_counter++;
    MP_INFO(ctx, "Recovered from display preemption.\n");
    return 1;
}