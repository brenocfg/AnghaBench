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
struct mpv_render_context {int had_kill_update; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  update_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kill_cb(void *ptr)
{
    struct mpv_render_context *ctx = ptr;

    pthread_mutex_lock(&ctx->update_lock);
    ctx->had_kill_update = true;
    pthread_cond_broadcast(&ctx->update_cond);
    pthread_mutex_unlock(&ctx->update_lock);
}