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
typedef  int /*<<< orphan*/  uint8_t ;
struct free_dr_context {struct dr_helper* dr; } ;
struct dr_helper {int /*<<< orphan*/  dispatch; int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread; scalar_t__ thread_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_thread_free (struct free_dr_context*) ; 
 int /*<<< orphan*/  mp_dispatch_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct free_dr_context*),struct free_dr_context*) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__((used)) static void free_dr_buffer_on_dr_thread(void *opaque, uint8_t *data)
{
    struct free_dr_context *ctx = opaque;
    struct dr_helper *dr = ctx->dr;

    pthread_mutex_lock(&dr->thread_lock);
    bool on_this_thread =
        dr->thread_valid && pthread_equal(ctx->dr->thread, pthread_self());
    pthread_mutex_unlock(&dr->thread_lock);

    // The image could be unreffed even on the DR thread. In practice, this
    // matters most on DR destruction.
    if (on_this_thread) {
        dr_thread_free(ctx);
    } else {
        mp_dispatch_enqueue(dr->dispatch, dr_thread_free, ctx);
    }
}