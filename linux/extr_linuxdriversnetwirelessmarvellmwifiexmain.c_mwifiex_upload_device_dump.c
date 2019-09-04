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
struct mwifiex_adapter {scalar_t__ devdump_len; int /*<<< orphan*/ * devdump_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  dev_coredumpv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 

void mwifiex_upload_device_dump(struct mwifiex_adapter *adapter)
{
	/* Dump all the memory data into single file, a userspace script will
	 * be used to split all the memory data to multiple files
	 */
	mwifiex_dbg(adapter, MSG,
		    "== mwifiex dump information to /sys/class/devcoredump start\n");
	dev_coredumpv(adapter->dev, adapter->devdump_data, adapter->devdump_len,
		      GFP_KERNEL);
	mwifiex_dbg(adapter, MSG,
		    "== mwifiex dump information to /sys/class/devcoredump end\n");

	/* Device dump data will be freed in device coredump release function
	 * after 5 min. Here reset adapter->devdump_data and ->devdump_len
	 * to avoid it been accidentally reused.
	 */
	adapter->devdump_data = NULL;
	adapter->devdump_len = 0;
}