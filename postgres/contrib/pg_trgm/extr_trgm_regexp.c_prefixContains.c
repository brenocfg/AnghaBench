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
struct TYPE_4__ {scalar_t__* colors; } ;
typedef  TYPE_1__ TrgmPrefix ;

/* Variables and functions */
 scalar_t__ COLOR_UNKNOWN ; 

__attribute__((used)) static bool
prefixContains(TrgmPrefix *prefix1, TrgmPrefix *prefix2)
{
	if (prefix1->colors[1] == COLOR_UNKNOWN)
	{
		/* Fully ambiguous prefix contains everything */
		return true;
	}
	else if (prefix1->colors[0] == COLOR_UNKNOWN)
	{
		/*
		 * Prefix with only first unknown color contains every prefix with
		 * same second color.
		 */
		if (prefix1->colors[1] == prefix2->colors[1])
			return true;
		else
			return false;
	}
	else
	{
		/* Exact prefix contains only the exact same prefix */
		if (prefix1->colors[0] == prefix2->colors[0] &&
			prefix1->colors[1] == prefix2->colors[1])
			return true;
		else
			return false;
	}
}