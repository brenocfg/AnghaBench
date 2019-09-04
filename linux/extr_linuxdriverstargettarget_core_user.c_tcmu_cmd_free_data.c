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
typedef  size_t uint32_t ;
struct tcmu_dev {int /*<<< orphan*/  data_bitmap; } ;
struct tcmu_cmd {int /*<<< orphan*/ * dbi; struct tcmu_dev* tcmu_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcmu_cmd_free_data(struct tcmu_cmd *tcmu_cmd, uint32_t len)
{
	struct tcmu_dev *udev = tcmu_cmd->tcmu_dev;
	uint32_t i;

	for (i = 0; i < len; i++)
		clear_bit(tcmu_cmd->dbi[i], udev->data_bitmap);
}