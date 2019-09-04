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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct flow_ports {void* source; void* dest; } ;
struct flow_offload {TYPE_2__* tuplehash; } ;
typedef  enum flow_offload_tuple_dir { ____Placeholder_flow_offload_tuple_dir } flow_offload_tuple_dir ;
typedef  void* __be16 ;
struct TYPE_3__ {void* dst_port; void* src_port; } ;
struct TYPE_4__ {TYPE_1__ tuple; } ;

/* Variables and functions */
#define  FLOW_OFFLOAD_DIR_ORIGINAL 129 
#define  FLOW_OFFLOAD_DIR_REPLY 128 
 int nf_flow_nat_port (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 scalar_t__ skb_try_make_writable (struct sk_buff*,unsigned int) ; 

int nf_flow_dnat_port(const struct flow_offload *flow,
		      struct sk_buff *skb, unsigned int thoff,
		      u8 protocol, enum flow_offload_tuple_dir dir)
{
	struct flow_ports *hdr;
	__be16 port, new_port;

	if (!pskb_may_pull(skb, thoff + sizeof(*hdr)) ||
	    skb_try_make_writable(skb, thoff + sizeof(*hdr)))
		return -1;

	hdr = (void *)(skb_network_header(skb) + thoff);

	switch (dir) {
	case FLOW_OFFLOAD_DIR_ORIGINAL:
		port = hdr->dest;
		new_port = flow->tuplehash[FLOW_OFFLOAD_DIR_REPLY].tuple.src_port;
		hdr->dest = new_port;
		break;
	case FLOW_OFFLOAD_DIR_REPLY:
		port = hdr->source;
		new_port = flow->tuplehash[FLOW_OFFLOAD_DIR_ORIGINAL].tuple.dst_port;
		hdr->source = new_port;
		break;
	default:
		return -1;
	}

	return nf_flow_nat_port(skb, thoff, protocol, port, new_port);
}