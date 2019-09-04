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
struct wl12xx_rx_filter {int num_fields; TYPE_1__* fields; } ;
struct TYPE_2__ {struct wl12xx_rx_filter* pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wl12xx_rx_filter*) ; 

void wl1271_rx_filter_free(struct wl12xx_rx_filter *filter)
{
	int i;

	if (filter == NULL)
		return;

	for (i = 0; i < filter->num_fields; i++)
		kfree(filter->fields[i].pattern);

	kfree(filter);
}