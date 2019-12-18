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
typedef  int /*<<< orphan*/  trgm ;
typedef  int /*<<< orphan*/  float4 ;
typedef  int /*<<< orphan*/  TRGM ;

/* Variables and functions */
 int ARRNELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALCSML (int,int,int) ; 
 int CMPTRGM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GETARR (int /*<<< orphan*/ *) ; 

float4
cnt_sml(TRGM *trg1, TRGM *trg2, bool inexact)
{
	trgm	   *ptr1,
			   *ptr2;
	int			count = 0;
	int			len1,
				len2;

	ptr1 = GETARR(trg1);
	ptr2 = GETARR(trg2);

	len1 = ARRNELEM(trg1);
	len2 = ARRNELEM(trg2);

	/* explicit test is needed to avoid 0/0 division when both lengths are 0 */
	if (len1 <= 0 || len2 <= 0)
		return (float4) 0.0;

	while (ptr1 - GETARR(trg1) < len1 && ptr2 - GETARR(trg2) < len2)
	{
		int			res = CMPTRGM(ptr1, ptr2);

		if (res < 0)
			ptr1++;
		else if (res > 0)
			ptr2++;
		else
		{
			ptr1++;
			ptr2++;
			count++;
		}
	}

	/*
	 * If inexact then len2 is equal to count, because we don't know actual
	 * length of second string in inexact search and we can assume that count
	 * is a lower bound of len2.
	 */
	return CALCSML(count, len1, inexact ? count : len2);
}