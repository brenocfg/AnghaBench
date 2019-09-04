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

/* Variables and functions */
 unsigned int MAX_ISC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ctl_set_bit (int,int) ; 
 int /*<<< orphan*/  isc_ref_lock ; 
 scalar_t__* isc_refs ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void isc_register(unsigned int isc)
{
	if (isc > MAX_ISC) {
		WARN_ON(1);
		return;
	}

	spin_lock(&isc_ref_lock);
	if (isc_refs[isc] == 0)
		ctl_set_bit(6, 31 - isc);
	isc_refs[isc]++;
	spin_unlock(&isc_ref_lock);
}