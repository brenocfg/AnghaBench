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
struct hvc_iucv_private {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hvc_iucv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hvc_iucv_hangup (struct hvc_iucv_private*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

__attribute__((used)) static int hvc_iucv_pm_freeze(struct device *dev)
{
	struct hvc_iucv_private *priv = dev_get_drvdata(dev);

	local_bh_disable();
	hvc_iucv_hangup(priv);
	local_bh_enable();

	return 0;
}