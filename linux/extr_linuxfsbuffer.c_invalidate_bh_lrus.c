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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  has_bh_in_lru ; 
 int /*<<< orphan*/  invalidate_bh_lru ; 
 int /*<<< orphan*/  on_each_cpu_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void invalidate_bh_lrus(void)
{
	on_each_cpu_cond(has_bh_in_lru, invalidate_bh_lru, NULL, 1, GFP_KERNEL);
}