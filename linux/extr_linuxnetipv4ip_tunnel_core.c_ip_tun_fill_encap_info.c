#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;
struct TYPE_6__ {int /*<<< orphan*/  tun_flags; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; TYPE_2__ u; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {TYPE_3__ key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LWTUNNEL_IP_DST ; 
 int /*<<< orphan*/  LWTUNNEL_IP_FLAGS ; 
 int /*<<< orphan*/  LWTUNNEL_IP_ID ; 
 int /*<<< orphan*/  LWTUNNEL_IP_PAD ; 
 int /*<<< orphan*/  LWTUNNEL_IP_SRC ; 
 int /*<<< orphan*/  LWTUNNEL_IP_TOS ; 
 int /*<<< orphan*/  LWTUNNEL_IP_TTL ; 
 struct ip_tunnel_info* lwt_tun_info (struct lwtunnel_state*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_tun_fill_encap_info(struct sk_buff *skb,
				  struct lwtunnel_state *lwtstate)
{
	struct ip_tunnel_info *tun_info = lwt_tun_info(lwtstate);

	if (nla_put_be64(skb, LWTUNNEL_IP_ID, tun_info->key.tun_id,
			 LWTUNNEL_IP_PAD) ||
	    nla_put_in_addr(skb, LWTUNNEL_IP_DST, tun_info->key.u.ipv4.dst) ||
	    nla_put_in_addr(skb, LWTUNNEL_IP_SRC, tun_info->key.u.ipv4.src) ||
	    nla_put_u8(skb, LWTUNNEL_IP_TOS, tun_info->key.tos) ||
	    nla_put_u8(skb, LWTUNNEL_IP_TTL, tun_info->key.ttl) ||
	    nla_put_be16(skb, LWTUNNEL_IP_FLAGS, tun_info->key.tun_flags))
		return -ENOMEM;

	return 0;
}