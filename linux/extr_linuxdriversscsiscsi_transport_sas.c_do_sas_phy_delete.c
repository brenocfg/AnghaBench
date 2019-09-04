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
 int /*<<< orphan*/  dev_to_phy (struct device*) ; 
 int /*<<< orphan*/  dev_to_sas_port (struct device*) ; 
 int /*<<< orphan*/  sas_phy_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_port_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_is_sas_phy (struct device*) ; 
 scalar_t__ scsi_is_sas_port (struct device*) ; 

__attribute__((used)) static int do_sas_phy_delete(struct device *dev, void *data)
{
	int pass = (int)(unsigned long)data;

	if (pass == 0 && scsi_is_sas_port(dev))
		sas_port_delete(dev_to_sas_port(dev));
	else if (pass == 1 && scsi_is_sas_phy(dev))
		sas_phy_delete(dev_to_phy(dev));
	return 0;
}