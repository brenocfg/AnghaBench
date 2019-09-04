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
struct sockaddr_ll {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_family; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  laddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  cfg_ifname ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_nametoindex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_bind(int fd)
{
	struct sockaddr_ll laddr = {0};

	laddr.sll_family = AF_PACKET;
	laddr.sll_protocol = htons(ETH_P_IP);
	laddr.sll_ifindex = if_nametoindex(cfg_ifname);
	if (!laddr.sll_ifindex)
		error(1, errno, "if_nametoindex");

	if (bind(fd, (void *)&laddr, sizeof(laddr)))
		error(1, errno, "bind");
}