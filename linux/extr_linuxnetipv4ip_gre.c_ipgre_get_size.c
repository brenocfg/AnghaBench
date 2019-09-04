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
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t ipgre_get_size(const struct net_device *dev)
{
	return
		/* IFLA_GRE_LINK */
		nla_total_size(4) +
		/* IFLA_GRE_IFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_OFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_IKEY */
		nla_total_size(4) +
		/* IFLA_GRE_OKEY */
		nla_total_size(4) +
		/* IFLA_GRE_LOCAL */
		nla_total_size(4) +
		/* IFLA_GRE_REMOTE */
		nla_total_size(4) +
		/* IFLA_GRE_TTL */
		nla_total_size(1) +
		/* IFLA_GRE_TOS */
		nla_total_size(1) +
		/* IFLA_GRE_PMTUDISC */
		nla_total_size(1) +
		/* IFLA_GRE_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_GRE_COLLECT_METADATA */
		nla_total_size(0) +
		/* IFLA_GRE_IGNORE_DF */
		nla_total_size(1) +
		/* IFLA_GRE_FWMARK */
		nla_total_size(4) +
		/* IFLA_GRE_ERSPAN_INDEX */
		nla_total_size(4) +
		/* IFLA_GRE_ERSPAN_VER */
		nla_total_size(1) +
		/* IFLA_GRE_ERSPAN_DIR */
		nla_total_size(1) +
		/* IFLA_GRE_ERSPAN_HWID */
		nla_total_size(2) +
		0;
}