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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_REENABLE_SIS_MODE ; 
 int sis_set_doorbell_bit (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 

int sis_reenable_sis_mode(struct pqi_ctrl_info *ctrl_info)
{
	return sis_set_doorbell_bit(ctrl_info, SIS_REENABLE_SIS_MODE);
}