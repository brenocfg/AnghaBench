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
 unsigned long HZ ; 
 scalar_t__ nlm_grace_period ; 
 int nlm_timeout ; 
 unsigned long roundup (scalar_t__,int) ; 

__attribute__((used)) static unsigned long get_lockd_grace_period(void)
{
	/* Note: nlm_timeout should always be nonzero */
	if (nlm_grace_period)
		return roundup(nlm_grace_period, nlm_timeout) * HZ;
	else
		return nlm_timeout * 5 * HZ;
}