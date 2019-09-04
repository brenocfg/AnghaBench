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
struct fcoe_ctlr_device {int dummy; } ;
struct fcoe_ctlr {scalar_t__ fip_resp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct fcoe_ctlr_device* dev_to_ctlr (struct device*) ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_ctlr_fip_resp(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	struct fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	struct fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr);

	return sprintf(buf, "%d\n", fip->fip_resp ? 1 : 0);
}