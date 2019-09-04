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
 int /*<<< orphan*/  DHCP_allocated_gw ; 
 int /*<<< orphan*/  DHCP_allocated_ip ; 
 int /*<<< orphan*/  DHCP_allocated_sn ; 
 int /*<<< orphan*/  setGAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSIPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSUBR (int /*<<< orphan*/ ) ; 

void default_ip_assign(void)
{
   setSIPR(DHCP_allocated_ip);
   setSUBR(DHCP_allocated_sn);
   setGAR (DHCP_allocated_gw);
}