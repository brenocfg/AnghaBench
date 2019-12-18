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
struct mp_vdpau_ctx {int is_preempted; int /*<<< orphan*/  preempt_lock; } ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void preemption_callback(VdpDevice device, void *context)
{
    struct mp_vdpau_ctx *ctx = context;

    pthread_mutex_lock(&ctx->preempt_lock);
    ctx->is_preempted = true;
    pthread_mutex_unlock(&ctx->preempt_lock);
}