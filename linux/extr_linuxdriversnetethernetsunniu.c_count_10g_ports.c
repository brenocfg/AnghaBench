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
struct phy_probe_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ port_has_10g (struct phy_probe_info*,int) ; 

__attribute__((used)) static int count_10g_ports(struct phy_probe_info *p, int *lowest)
{
	int port, cnt;

	cnt = 0;
	*lowest = 32;
	for (port = 8; port < 32; port++) {
		if (port_has_10g(p, port)) {
			if (!cnt)
				*lowest = port;
			cnt++;
		}
	}

	return cnt;
}