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
struct tcmu_dev {int dummy; } ;
struct tcmu_cmd {int dbi_cur; int dbi_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcmu_get_empty_block (struct tcmu_dev*,struct tcmu_cmd*) ; 

__attribute__((used)) static bool tcmu_get_empty_blocks(struct tcmu_dev *udev,
				  struct tcmu_cmd *tcmu_cmd)
{
	int i;

	for (i = tcmu_cmd->dbi_cur; i < tcmu_cmd->dbi_cnt; i++) {
		if (!tcmu_get_empty_block(udev, tcmu_cmd))
			return false;
	}
	return true;
}