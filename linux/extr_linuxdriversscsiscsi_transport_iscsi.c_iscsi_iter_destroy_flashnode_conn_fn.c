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
 int iscsi_destroy_flashnode_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_dev_to_flash_conn (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_flashnode_conn_dev (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_iter_destroy_flashnode_conn_fn(struct device *dev, void *data)
{
	if (!iscsi_is_flashnode_conn_dev(dev, NULL))
		return 0;

	return iscsi_destroy_flashnode_conn(iscsi_dev_to_flash_conn(dev));
}