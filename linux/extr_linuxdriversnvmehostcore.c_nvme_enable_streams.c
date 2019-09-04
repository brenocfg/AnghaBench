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
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int nvme_toggle_streams (struct nvme_ctrl*,int) ; 

__attribute__((used)) static int nvme_enable_streams(struct nvme_ctrl *ctrl)
{
	return nvme_toggle_streams(ctrl, true);
}