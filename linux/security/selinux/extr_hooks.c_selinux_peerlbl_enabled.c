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

/* Variables and functions */
 scalar_t__ netlbl_enabled () ; 
 scalar_t__ selinux_policycap_alwaysnetwork () ; 
 scalar_t__ selinux_xfrm_enabled () ; 

__attribute__((used)) static int selinux_peerlbl_enabled(void)
{
	return (selinux_policycap_alwaysnetwork() ||
		netlbl_enabled() || selinux_xfrm_enabled());
}