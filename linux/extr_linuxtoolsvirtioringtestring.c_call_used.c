#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  call_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  used_idx; int /*<<< orphan*/  called_used_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  call () ; 
 TYPE_2__* event ; 
 TYPE_1__ host ; 
 int need_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

void call_used(void)
{
	bool need;

	/* Flush in previous flags write */
	/* Barrier D (for pairing) */
	smp_mb();

	need = need_event(event->call_index,
			host.used_idx,
			host.called_used_idx);

	host.called_used_idx = host.used_idx;

	if (need)
		call();
}