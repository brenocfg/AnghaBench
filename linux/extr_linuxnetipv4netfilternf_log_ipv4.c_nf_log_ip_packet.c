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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {int dummy; } ;
struct nf_loginfo {int dummy; } ;
struct nf_log_buf {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_loginfo default_loginfo ; 
 int /*<<< orphan*/  dump_ipv4_mac_header (struct nf_log_buf*,struct nf_loginfo const*,struct sk_buff const*) ; 
 int /*<<< orphan*/  dump_ipv4_packet (struct net*,struct nf_log_buf*,struct nf_loginfo const*,struct sk_buff const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_buf_close (struct nf_log_buf*) ; 
 struct nf_log_buf* nf_log_buf_open () ; 
 int /*<<< orphan*/  nf_log_dump_packet_common (struct nf_log_buf*,int /*<<< orphan*/ ,unsigned int,struct sk_buff const*,struct net_device const*,struct net_device const*,struct nf_loginfo const*,char const*) ; 
 int /*<<< orphan*/  sysctl_nf_log_all_netns ; 

__attribute__((used)) static void nf_log_ip_packet(struct net *net, u_int8_t pf,
			     unsigned int hooknum, const struct sk_buff *skb,
			     const struct net_device *in,
			     const struct net_device *out,
			     const struct nf_loginfo *loginfo,
			     const char *prefix)
{
	struct nf_log_buf *m;

	/* FIXME: Disabled from containers until syslog ns is supported */
	if (!net_eq(net, &init_net) && !sysctl_nf_log_all_netns)
		return;

	m = nf_log_buf_open();

	if (!loginfo)
		loginfo = &default_loginfo;

	nf_log_dump_packet_common(m, pf, hooknum, skb, in,
				  out, loginfo, prefix);

	if (in != NULL)
		dump_ipv4_mac_header(m, loginfo, skb);

	dump_ipv4_packet(net, m, loginfo, skb, 0);

	nf_log_buf_close(m);
}