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
 int /*<<< orphan*/  DHCP_CHADDR ; 
 int /*<<< orphan*/  MR_RST ; 
 int /*<<< orphan*/  default_ip_assign () ; 
 int /*<<< orphan*/  getMR () ; 
 int /*<<< orphan*/  setMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSHAR (int /*<<< orphan*/ ) ; 

void default_ip_update(void)
{
	/* WIZchip Software Reset */
   setMR(MR_RST);
   getMR(); // for delay
   default_ip_assign();
   setSHAR(DHCP_CHADDR);
}