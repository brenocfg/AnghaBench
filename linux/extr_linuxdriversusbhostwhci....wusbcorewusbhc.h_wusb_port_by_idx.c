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
typedef  size_t u8 ;
struct wusbhc {struct wusb_port* port; } ;
struct wusb_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct wusb_port *wusb_port_by_idx(struct wusbhc *wusbhc,
						 u8 port_idx)
{
	return &wusbhc->port[port_idx];
}