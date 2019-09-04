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
struct usbnet {int dummy; } ;
struct mcs7830_data {int /*<<< orphan*/  multi_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_REG_MULTICAST_HASH ; 
 struct mcs7830_data* mcs7830_get_data (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_set_reg_async (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcs7830_hif_update_multicast_hash(struct usbnet *dev)
{
	struct mcs7830_data *data = mcs7830_get_data(dev);
	mcs7830_set_reg_async(dev, HIF_REG_MULTICAST_HASH,
				sizeof data->multi_filter,
				data->multi_filter);
}