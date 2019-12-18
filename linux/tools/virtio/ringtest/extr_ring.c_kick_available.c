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
struct TYPE_4__ {int /*<<< orphan*/  kick_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  avail_idx; int /*<<< orphan*/  kicked_avail_idx; } ;

/* Variables and functions */
 TYPE_2__* event ; 
 TYPE_1__ guest ; 
 int /*<<< orphan*/  kick () ; 
 int need_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

void kick_available(void)
{
	bool need;

	/* Flush in previous flags write */
	/* Barrier C (for pairing) */
	smp_mb();
	need = need_event(event->kick_index,
			   guest.avail_idx,
			   guest.kicked_avail_idx);

	guest.kicked_avail_idx = guest.avail_idx;
	if (need)
		kick();
}