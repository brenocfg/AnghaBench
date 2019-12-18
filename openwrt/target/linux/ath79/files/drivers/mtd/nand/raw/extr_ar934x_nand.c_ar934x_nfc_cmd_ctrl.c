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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void ar934x_nfc_cmd_ctrl(struct mtd_info *mtd, int dat,
				unsigned int ctrl)
{
	WARN_ON(dat != NAND_CMD_NONE);
}