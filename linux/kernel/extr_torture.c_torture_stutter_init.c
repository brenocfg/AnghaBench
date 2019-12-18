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
 int stutter ; 
 int stutter_gap ; 
 int /*<<< orphan*/  stutter_task ; 
 int torture_create_kthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  torture_stutter ; 

int torture_stutter_init(const int s, const int sgap)
{
	stutter = s;
	stutter_gap = sgap;
	return torture_create_kthread(torture_stutter, NULL, stutter_task);
}