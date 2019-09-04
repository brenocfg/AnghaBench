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
 int /*<<< orphan*/  bpf_set_link_xdp_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/ * ifindex_list ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  sock_arp ; 
 int total_ifindex ; 

__attribute__((used)) static void close_and_exit(int sig)
{
	int i = 0;

	close(sock);
	close(sock_arp);

	for (i = 0; i < total_ifindex; i++)
		bpf_set_link_xdp_fd(ifindex_list[i], -1, flags);
	exit(0);
}