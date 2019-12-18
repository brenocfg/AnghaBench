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
struct ib_device_attr {int device_cap_flags; scalar_t__ max_fast_reg_page_list_len; } ;
struct ib_device {int /*<<< orphan*/  name; struct ib_device_attr attrs; } ;

/* Variables and functions */
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

bool frwr_is_supported(struct ib_device *device)
{
	struct ib_device_attr *attrs = &device->attrs;

	if (!(attrs->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		goto out_not_supported;
	if (attrs->max_fast_reg_page_list_len == 0)
		goto out_not_supported;
	return true;

out_not_supported:
	pr_info("rpcrdma: 'frwr' mode is not supported by device %s\n",
		device->name);
	return false;
}