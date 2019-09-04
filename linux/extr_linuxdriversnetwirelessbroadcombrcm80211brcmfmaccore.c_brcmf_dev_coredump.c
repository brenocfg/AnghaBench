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
struct brcmf_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ brcmf_debug_create_memdump (struct brcmf_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 

void brcmf_dev_coredump(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);

	if (brcmf_debug_create_memdump(bus_if, NULL, 0) < 0)
		brcmf_dbg(TRACE, "failed to create coredump\n");
}