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
struct p54u_priv {int /*<<< orphan*/  submitted; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p54u_free_urbs(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	usb_kill_anchored_urbs(&priv->submitted);
}