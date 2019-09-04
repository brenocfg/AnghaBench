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
struct usbatm_data {int dummy; } ;
struct atm_dev {struct usbatm_data* dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbatm_put_instance (struct usbatm_data*) ; 

__attribute__((used)) static void usbatm_atm_dev_close(struct atm_dev *atm_dev)
{
	struct usbatm_data *instance = atm_dev->dev_data;

	if (!instance)
		return;

	atm_dev->dev_data = NULL; /* catch bugs */
	usbatm_put_instance(instance);	/* taken in usbatm_atm_init */
}