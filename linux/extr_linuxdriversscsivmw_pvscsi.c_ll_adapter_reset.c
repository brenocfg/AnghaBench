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
struct pvscsi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_CMD_ADAPTER_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct pvscsi_adapter const*) ; 
 int /*<<< orphan*/  pvscsi_dev (struct pvscsi_adapter const*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd_desc (struct pvscsi_adapter const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ll_adapter_reset(const struct pvscsi_adapter *adapter)
{
	dev_dbg(pvscsi_dev(adapter), "Adapter Reset on %p\n", adapter);

	pvscsi_write_cmd_desc(adapter, PVSCSI_CMD_ADAPTER_RESET, NULL, 0);
}