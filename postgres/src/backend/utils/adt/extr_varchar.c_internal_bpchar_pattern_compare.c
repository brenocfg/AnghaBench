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
typedef  int /*<<< orphan*/  BpChar ;

/* Variables and functions */
 int /*<<< orphan*/  Min (int,int) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int bcTruelen (int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
internal_bpchar_pattern_compare(BpChar *arg1, BpChar *arg2)
{
	int			result;
	int			len1,
				len2;

	len1 = bcTruelen(arg1);
	len2 = bcTruelen(arg2);

	result = memcmp(VARDATA_ANY(arg1), VARDATA_ANY(arg2), Min(len1, len2));
	if (result != 0)
		return result;
	else if (len1 < len2)
		return -1;
	else if (len1 > len2)
		return 1;
	else
		return 0;
}