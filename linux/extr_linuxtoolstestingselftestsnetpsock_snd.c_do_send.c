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
struct virtio_net_hdr {int dummy; } ;
struct sockaddr_ll {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  laddr ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  cfg_ifname ; 
 scalar_t__ cfg_use_bind ; 
 scalar_t__ cfg_use_dgram ; 
 int /*<<< orphan*/  cfg_use_vnet ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_nametoindex (int /*<<< orphan*/ ) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void do_send(int fd, char *buf, int len)
{
	int ret;

	if (!cfg_use_vnet) {
		buf += sizeof(struct virtio_net_hdr);
		len -= sizeof(struct virtio_net_hdr);
	}
	if (cfg_use_dgram) {
		buf += ETH_HLEN;
		len -= ETH_HLEN;
	}

	if (cfg_use_bind) {
		ret = write(fd, buf, len);
	} else {
		struct sockaddr_ll laddr = {0};

		laddr.sll_protocol = htons(ETH_P_IP);
		laddr.sll_ifindex = if_nametoindex(cfg_ifname);
		if (!laddr.sll_ifindex)
			error(1, errno, "if_nametoindex");

		ret = sendto(fd, buf, len, 0, (void *)&laddr, sizeof(laddr));
	}

	if (ret == -1)
		error(1, errno, "write");
	if (ret != len)
		error(1, 0, "write: %u %u", ret, len);

	fprintf(stderr, "tx: %u\n", ret);
}