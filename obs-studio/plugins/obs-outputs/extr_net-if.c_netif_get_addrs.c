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
struct netif_saddr_data {int /*<<< orphan*/  addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_get_addrs_nix (struct netif_saddr_data*) ; 
 int /*<<< orphan*/  netif_get_addrs_win32 (struct netif_saddr_data*) ; 

void netif_get_addrs(struct netif_saddr_data *ifaddrs)
{
	da_init(ifaddrs->addrs);

#ifdef _WIN32
	netif_get_addrs_win32(ifaddrs);
#else
	netif_get_addrs_nix(ifaddrs);
#endif
}