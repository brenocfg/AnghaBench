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
struct net_device {TYPE_1__* wireless_data; } ;
struct iw_spy_data {int dummy; } ;
struct TYPE_2__ {struct iw_spy_data* spy_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct iw_spy_data *get_spydata(struct net_device *dev)
{
	/* This is the new way */
	if (dev->wireless_data)
		return dev->wireless_data->spy_data;
	return NULL;
}