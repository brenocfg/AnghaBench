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
struct sk_buff {int dummy; } ;
struct ip_tunnel_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  options_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int __ip_tun_to_nlattr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  ip_tunnel_info_opts (struct ip_tunnel_info*) ; 

int ovs_nla_put_tunnel_info(struct sk_buff *skb,
			    struct ip_tunnel_info *tun_info)
{
	return __ip_tun_to_nlattr(skb, &tun_info->key,
				  ip_tunnel_info_opts(tun_info),
				  tun_info->options_len,
				  ip_tunnel_info_af(tun_info), tun_info->mode);
}