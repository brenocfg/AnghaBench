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
 int nfs4_delay_interruptible (long*) ; 
 int nfs4_delay_killable (long*) ; 

__attribute__((used)) static int nfs4_delay(long *timeout, bool interruptible)
{
	if (interruptible)
		return nfs4_delay_interruptible(timeout);
	return nfs4_delay_killable(timeout);
}