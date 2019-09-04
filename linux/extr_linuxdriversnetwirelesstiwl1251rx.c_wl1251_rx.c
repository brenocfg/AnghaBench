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
struct wl1251_rx_descriptor {int dummy; } ;
struct wl1251 {scalar_t__ state; struct wl1251_rx_descriptor* rx_descriptor; } ;

/* Variables and functions */
 scalar_t__ WL1251_STATE_ON ; 
 int /*<<< orphan*/  wl1251_rx_ack (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_rx_body (struct wl1251*,struct wl1251_rx_descriptor*) ; 
 int /*<<< orphan*/  wl1251_rx_header (struct wl1251*,struct wl1251_rx_descriptor*) ; 

void wl1251_rx(struct wl1251 *wl)
{
	struct wl1251_rx_descriptor *rx_desc;

	if (wl->state != WL1251_STATE_ON)
		return;

	rx_desc = wl->rx_descriptor;

	/* We first read the frame's header */
	wl1251_rx_header(wl, rx_desc);

	/* Now we can read the body */
	wl1251_rx_body(wl, rx_desc);

	/* Finally, we need to ACK the RX */
	wl1251_rx_ack(wl);
}