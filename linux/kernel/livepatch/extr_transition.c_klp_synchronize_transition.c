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
 int /*<<< orphan*/  klp_sync ; 
 int /*<<< orphan*/  schedule_on_each_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void klp_synchronize_transition(void)
{
	schedule_on_each_cpu(klp_sync);
}