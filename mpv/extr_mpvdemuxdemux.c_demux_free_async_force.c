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
struct demux_internal {TYPE_1__* d_user; } ;
struct demux_free_async_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_cancel_trigger (int /*<<< orphan*/ ) ; 

void demux_free_async_force(struct demux_free_async_state *state)
{
    struct demux_internal *in = (struct demux_internal *)state; // reverse lies

    mp_cancel_trigger(in->d_user->cancel);
}