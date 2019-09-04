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
struct TYPE_2__ {int /*<<< orphan*/  used_idx; int /*<<< orphan*/  called_used_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  call () ; 
 TYPE_1__ host ; 
 int /*<<< orphan*/  ring ; 
 int /*<<< orphan*/  smp_mb () ; 
 int vring_need_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_used_event (int /*<<< orphan*/ *) ; 

void call_used(void)
{
	bool need;

	/* Flush in previous flags write */
	/* Barrier D (for pairing) */
	smp_mb();
	need = vring_need_event(vring_used_event(&ring),
				host.used_idx,
				host.called_used_idx);

	host.called_used_idx = host.used_idx;
	if (need)
		call();
}