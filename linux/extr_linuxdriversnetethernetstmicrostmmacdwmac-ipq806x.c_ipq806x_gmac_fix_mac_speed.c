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
struct ipq806x_gmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipq806x_gmac_set_speed (struct ipq806x_gmac*,unsigned int) ; 

__attribute__((used)) static void ipq806x_gmac_fix_mac_speed(void *priv, unsigned int speed)
{
	struct ipq806x_gmac *gmac = priv;

	ipq806x_gmac_set_speed(gmac, speed);
}