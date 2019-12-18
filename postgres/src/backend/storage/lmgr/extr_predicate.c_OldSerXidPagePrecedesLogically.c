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
 int /*<<< orphan*/  Assert (int) ; 
 int OLDSERXID_MAX_PAGE ; 

__attribute__((used)) static bool
OldSerXidPagePrecedesLogically(int p, int q)
{
	int			diff;

	/*
	 * We have to compare modulo (OLDSERXID_MAX_PAGE+1)/2.  Both inputs should
	 * be in the range 0..OLDSERXID_MAX_PAGE.
	 */
	Assert(p >= 0 && p <= OLDSERXID_MAX_PAGE);
	Assert(q >= 0 && q <= OLDSERXID_MAX_PAGE);

	diff = p - q;
	if (diff >= ((OLDSERXID_MAX_PAGE + 1) / 2))
		diff -= OLDSERXID_MAX_PAGE + 1;
	else if (diff < -((int) (OLDSERXID_MAX_PAGE + 1) / 2))
		diff += OLDSERXID_MAX_PAGE + 1;
	return diff < 0;
}