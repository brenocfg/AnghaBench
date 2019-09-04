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
 int /*<<< orphan*/  action_fifos ; 
 int /*<<< orphan*/  flow_keys ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 

void action_fifos_exit(void)
{
	free_percpu(action_fifos);
	free_percpu(flow_keys);
}