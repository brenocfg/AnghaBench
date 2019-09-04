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
typedef  int u32 ;
struct wl1271_rx_descriptor {int dummy; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 wl18xx_get_rx_packet_len(struct wl1271 *wl, void *rx_data,
				    u32 data_len)
{
	struct wl1271_rx_descriptor *desc = rx_data;

	/* invalid packet */
	if (data_len < sizeof(*desc))
		return 0;

	return data_len - sizeof(*desc);
}