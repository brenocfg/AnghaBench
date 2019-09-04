#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kernelid_map_lock; int /*<<< orphan*/  kernelid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sm_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_kernel_id(int handle)
{
	spin_lock(&sm_state->kernelid_map_lock);
	idr_remove(&sm_state->kernelid_map, handle);
	spin_unlock(&sm_state->kernelid_map_lock);
}