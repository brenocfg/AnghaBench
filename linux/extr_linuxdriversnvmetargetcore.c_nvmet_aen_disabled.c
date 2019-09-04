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
typedef  int u32 ;
struct nvmet_ctrl {int /*<<< orphan*/  aen_masked; int /*<<< orphan*/  aen_enabled; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nvmet_aen_disabled(struct nvmet_ctrl *ctrl, u32 aen)
{
	if (!(READ_ONCE(ctrl->aen_enabled) & aen))
		return true;
	return test_and_set_bit(aen, &ctrl->aen_masked);
}