#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ sll_halen; scalar_t__ sll_pkttype; scalar_t__ sll_hatype; int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_family; } ;
struct ring {TYPE_1__ ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_nametoindex (char*) ; 
 int /*<<< orphan*/  pair_udp_setfilter (int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void bind_ring(int sock, struct ring *ring)
{
	int ret;

	pair_udp_setfilter(sock);

	ring->ll.sll_family = PF_PACKET;
	ring->ll.sll_protocol = htons(ETH_P_ALL);
	ring->ll.sll_ifindex = if_nametoindex("lo");
	ring->ll.sll_hatype = 0;
	ring->ll.sll_pkttype = 0;
	ring->ll.sll_halen = 0;

	ret = bind(sock, (struct sockaddr *) &ring->ll, sizeof(ring->ll));
	if (ret == -1) {
		perror("bind");
		exit(1);
	}
}