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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct ip_tunnel_key {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_TUNNEL ; 
 int __ip_tun_to_nlattr (struct sk_buff*,struct ip_tunnel_key const*,void const*,int,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_tun_to_nlattr(struct sk_buff *skb,
			    const struct ip_tunnel_key *output,
			    const void *tun_opts, int swkey_tun_opts_len,
			    unsigned short tun_proto, u8 mode)
{
	struct nlattr *nla;
	int err;

	nla = nla_nest_start_noflag(skb, OVS_KEY_ATTR_TUNNEL);
	if (!nla)
		return -EMSGSIZE;

	err = __ip_tun_to_nlattr(skb, output, tun_opts, swkey_tun_opts_len,
				 tun_proto, mode);
	if (err)
		return err;

	nla_nest_end(skb, nla);
	return 0;
}