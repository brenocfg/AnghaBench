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
typedef  int /*<<< orphan*/  uint8_t ;
struct free_dr_context {TYPE_1__* dr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispatch; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_thread_free (struct free_dr_context*) ; 
 int /*<<< orphan*/  mp_dispatch_run (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct free_dr_context*),struct free_dr_context*) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__((used)) static void free_dr_buffer_on_dr_thread(void *opaque, uint8_t *data)
{
    struct free_dr_context *ctx = opaque;

    // The image could be unreffed even on the DR thread. In practice, this
    // matters most on DR destruction.
    if (pthread_equal(ctx->dr->thread, pthread_self())) {
        dr_thread_free(ctx);
    } else {
        mp_dispatch_run(ctx->dr->dispatch, dr_thread_free, ctx);
    }
}