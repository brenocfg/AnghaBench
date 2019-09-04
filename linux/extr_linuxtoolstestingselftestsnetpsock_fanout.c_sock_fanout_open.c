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
typedef  int /*<<< orphan*/  val ;
typedef  int uint16_t ;
struct sockaddr_ll {scalar_t__ sll_ifindex; int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_family; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  PACKET_FANOUT ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 scalar_t__ bind (int,void*,int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ if_nametoindex (char*) ; 
 int /*<<< orphan*/  pair_udp_setfilter (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sock_fanout_open(uint16_t typeflags, uint16_t group_id)
{
	struct sockaddr_ll addr = {0};
	int fd, val;

	fd = socket(PF_PACKET, SOCK_RAW, 0);
	if (fd < 0) {
		perror("socket packet");
		exit(1);
	}

	pair_udp_setfilter(fd);

	addr.sll_family = AF_PACKET;
	addr.sll_protocol = htons(ETH_P_IP);
	addr.sll_ifindex = if_nametoindex("lo");
	if (addr.sll_ifindex == 0) {
		perror("if_nametoindex");
		exit(1);
	}
	if (bind(fd, (void *) &addr, sizeof(addr))) {
		perror("bind packet");
		exit(1);
	}

	val = (((int) typeflags) << 16) | group_id;
	if (setsockopt(fd, SOL_PACKET, PACKET_FANOUT, &val, sizeof(val))) {
		if (close(fd)) {
			perror("close packet");
			exit(1);
		}
		return -1;
	}

	return fd;
}