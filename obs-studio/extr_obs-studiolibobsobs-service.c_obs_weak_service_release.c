#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_weak_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 scalar_t__ obs_weak_ref_release (int /*<<< orphan*/ *) ; 

void obs_weak_service_release(obs_weak_service_t *weak)
{
	if (!weak)
		return;

	if (obs_weak_ref_release(&weak->ref))
		bfree(weak);
}