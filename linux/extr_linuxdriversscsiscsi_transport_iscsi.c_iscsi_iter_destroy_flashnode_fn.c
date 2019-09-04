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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_destroy_flashnode_sess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_dev_to_flash_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_flashnode_bus_match (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_iter_destroy_flashnode_fn(struct device *dev, void *data)
{
	if (!iscsi_flashnode_bus_match(dev, NULL))
		return 0;

	iscsi_destroy_flashnode_sess(iscsi_dev_to_flash_session(dev));
	return 0;
}