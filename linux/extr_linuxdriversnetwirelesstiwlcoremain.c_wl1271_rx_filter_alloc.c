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
struct wl12xx_rx_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wl12xx_rx_filter* kzalloc (int,int /*<<< orphan*/ ) ; 

struct wl12xx_rx_filter *wl1271_rx_filter_alloc(void)
{
	return kzalloc(sizeof(struct wl12xx_rx_filter), GFP_KERNEL);
}