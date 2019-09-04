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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipw_led_link_on (struct ipw_priv*) ; 

__attribute__((used)) static void ipw_led_link_up(struct ipw_priv *priv)
{
	/* Set the Link Led on for all nic types */
	ipw_led_link_on(priv);
}