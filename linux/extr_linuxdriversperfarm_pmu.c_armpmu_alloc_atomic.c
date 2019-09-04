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
struct arm_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct arm_pmu* __armpmu_alloc (int /*<<< orphan*/ ) ; 

struct arm_pmu *armpmu_alloc_atomic(void)
{
	return __armpmu_alloc(GFP_ATOMIC);
}