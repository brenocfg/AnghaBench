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
typedef  int u8 ;
struct se_device {int dummy; } ;
struct se_cmd {struct se_device* se_dev; } ;

/* Variables and functions */
 scalar_t__ target_check_wce (struct se_device*) ; 

__attribute__((used)) static int spc_modesense_caching(struct se_cmd *cmd, u8 pc, u8 *p)
{
	struct se_device *dev = cmd->se_dev;

	p[0] = 0x08;
	p[1] = 0x12;

	/* No changeable values for now */
	if (pc == 1)
		goto out;

	if (target_check_wce(dev))
		p[2] = 0x04; /* Write Cache Enable */
	p[12] = 0x20; /* Disabled Read Ahead */

out:
	return 20;
}