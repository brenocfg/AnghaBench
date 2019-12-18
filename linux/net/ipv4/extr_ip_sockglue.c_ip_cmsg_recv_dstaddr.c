#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_zero; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  _ports ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IP_ORIGDSTADDR ; 
 int /*<<< orphan*/  SOL_IP ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sockaddr_in*) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static void ip_cmsg_recv_dstaddr(struct msghdr *msg, struct sk_buff *skb)
{
	__be16 _ports[2], *ports;
	struct sockaddr_in sin;

	/* All current transport protocols have the port numbers in the
	 * first four bytes of the transport header and this function is
	 * written with this assumption in mind.
	 */
	ports = skb_header_pointer(skb, skb_transport_offset(skb),
				   sizeof(_ports), &_ports);
	if (!ports)
		return;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ip_hdr(skb)->daddr;
	sin.sin_port = ports[1];
	memset(sin.sin_zero, 0, sizeof(sin.sin_zero));

	put_cmsg(msg, SOL_IP, IP_ORIGDSTADDR, sizeof(sin), &sin);
}