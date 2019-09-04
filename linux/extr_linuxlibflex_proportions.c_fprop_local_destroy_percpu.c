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
struct fprop_local_percpu {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 

void fprop_local_destroy_percpu(struct fprop_local_percpu *pl)
{
	percpu_counter_destroy(&pl->events);
}