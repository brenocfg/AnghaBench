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
struct wl1271 {int dummy; } ;
typedef  enum wl_rx_buf_align { ____Placeholder_wl_rx_buf_align } wl_rx_buf_align ;

/* Variables and functions */
 int RX_BUF_PADDED_PAYLOAD ; 
 int WLCORE_RX_BUF_ALIGNED ; 
 int WLCORE_RX_BUF_PADDED ; 

__attribute__((used)) static enum wl_rx_buf_align
wl18xx_get_rx_buf_align(struct wl1271 *wl, u32 rx_desc)
{
	if (rx_desc & RX_BUF_PADDED_PAYLOAD)
		return WLCORE_RX_BUF_PADDED;

	return WLCORE_RX_BUF_ALIGNED;
}