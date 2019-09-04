#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_dev ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {scalar_t__ irq_wakeup; TYPE_1__ if_ops; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_free_adapter (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_uninit_sw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 

int mwifiex_remove_card(struct mwifiex_adapter *adapter)
{
	if (!adapter)
		return 0;

	mwifiex_uninit_sw(adapter);

	if (adapter->irq_wakeup >= 0)
		device_init_wakeup(adapter->dev, false);

	/* Unregister device */
	mwifiex_dbg(adapter, INFO,
		    "info: unregister device\n");
	if (adapter->if_ops.unregister_dev)
		adapter->if_ops.unregister_dev(adapter);
	/* Free adapter structure */
	mwifiex_dbg(adapter, INFO,
		    "info: free adapter\n");
	mwifiex_free_adapter(adapter);

	return 0;
}