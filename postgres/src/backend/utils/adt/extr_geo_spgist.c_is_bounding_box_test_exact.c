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
typedef  int StrategyNumber ;

/* Variables and functions */
#define  RTAboveStrategyNumber 135 
#define  RTBelowStrategyNumber 134 
#define  RTLeftStrategyNumber 133 
#define  RTOverAboveStrategyNumber 132 
#define  RTOverBelowStrategyNumber 131 
#define  RTOverLeftStrategyNumber 130 
#define  RTOverRightStrategyNumber 129 
#define  RTRightStrategyNumber 128 

__attribute__((used)) static bool
is_bounding_box_test_exact(StrategyNumber strategy)
{
	switch (strategy)
	{
		case RTLeftStrategyNumber:
		case RTOverLeftStrategyNumber:
		case RTOverRightStrategyNumber:
		case RTRightStrategyNumber:
		case RTOverBelowStrategyNumber:
		case RTBelowStrategyNumber:
		case RTAboveStrategyNumber:
		case RTOverAboveStrategyNumber:
			return true;

		default:
			return false;
	}
}