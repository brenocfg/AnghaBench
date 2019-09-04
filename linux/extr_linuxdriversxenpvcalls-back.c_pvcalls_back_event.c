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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct pvcalls_fedata {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct pvcalls_fedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvcalls_back_work (struct pvcalls_fedata*) ; 

__attribute__((used)) static irqreturn_t pvcalls_back_event(int irq, void *dev_id)
{
	struct xenbus_device *dev = dev_id;
	struct pvcalls_fedata *fedata = NULL;

	if (dev == NULL)
		return IRQ_HANDLED;

	fedata = dev_get_drvdata(&dev->dev);
	if (fedata == NULL)
		return IRQ_HANDLED;

	pvcalls_back_work(fedata);
	return IRQ_HANDLED;
}