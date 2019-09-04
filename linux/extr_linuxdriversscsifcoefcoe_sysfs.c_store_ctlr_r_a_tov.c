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
struct fcoe_ctlr_device {scalar_t__ enabled; } ;
struct fcoe_ctlr {TYPE_1__* lp; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  r_a_tov; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 scalar_t__ FCOE_CTLR_DISABLED ; 
 scalar_t__ FCOE_CTLR_ENABLED ; 
 struct fcoe_ctlr_device* dev_to_ctlr (struct device*) ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 int /*<<< orphan*/  fcoe_ctlr_var_store (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static ssize_t store_ctlr_r_a_tov(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct fcoe_ctlr_device *ctlr_dev = dev_to_ctlr(dev);
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);

	if (ctlr_dev->enabled == FCOE_CTLR_ENABLED)
		return -EBUSY;
	if (ctlr_dev->enabled == FCOE_CTLR_DISABLED)
		return fcoe_ctlr_var_store(&ctlr->lp->r_a_tov, buf, count);
	return -ENOTSUPP;
}