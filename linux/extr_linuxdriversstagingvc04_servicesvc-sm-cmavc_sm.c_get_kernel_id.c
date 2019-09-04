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
struct vc_sm_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernelid_map_lock; int /*<<< orphan*/  kernelid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,struct vc_sm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sm_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_kernel_id(struct vc_sm_buffer *buffer)
{
	int handle;

	spin_lock(&sm_state->kernelid_map_lock);
	handle = idr_alloc(&sm_state->kernelid_map, buffer, 0, 0, GFP_KERNEL);
	spin_unlock(&sm_state->kernelid_map_lock);

	return handle;
}