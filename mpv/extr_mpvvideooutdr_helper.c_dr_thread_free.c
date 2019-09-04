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
struct free_dr_context {int /*<<< orphan*/  ref; TYPE_1__* dr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dr_in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (unsigned long long) ; 
 unsigned long long atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct free_dr_context*) ; 

__attribute__((used)) static void dr_thread_free(void *ptr)
{
    struct free_dr_context *ctx = ptr;

    unsigned long long v = atomic_fetch_add(&ctx->dr->dr_in_flight, -1);
    assert(v); // value before sub is 0 - unexpected underflow.

    av_buffer_unref(&ctx->ref);
    talloc_free(ctx);
}