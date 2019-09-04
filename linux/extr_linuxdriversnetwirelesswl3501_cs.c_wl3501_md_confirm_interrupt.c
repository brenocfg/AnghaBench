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
typedef  int /*<<< orphan*/  u16 ;
struct wl3501_md_confirm {int /*<<< orphan*/  data; } ;
struct wl3501_card {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wl3501_free_tx_buffer (struct wl3501_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl3501_get_from_wla (struct wl3501_card*,int /*<<< orphan*/ ,struct wl3501_md_confirm*,int) ; 

__attribute__((used)) static inline void wl3501_md_confirm_interrupt(struct net_device *dev,
					       struct wl3501_card *this,
					       u16 addr)
{
	struct wl3501_md_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, sizeof(sig));
	wl3501_free_tx_buffer(this, sig.data);
	if (netif_queue_stopped(dev))
		netif_wake_queue(dev);
}