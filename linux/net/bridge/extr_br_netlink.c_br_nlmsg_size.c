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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ifinfomsg {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int MAX_ADDR_LEN ; 
 size_t NLMSG_ALIGN (int) ; 
 int br_get_link_af_size_filtered (struct net_device*,int /*<<< orphan*/ ) ; 
 int br_port_info_size () ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t br_nlmsg_size(struct net_device *dev, u32 filter_mask)
{
	return NLMSG_ALIGN(sizeof(struct ifinfomsg))
		+ nla_total_size(IFNAMSIZ) /* IFLA_IFNAME */
		+ nla_total_size(MAX_ADDR_LEN) /* IFLA_ADDRESS */
		+ nla_total_size(4) /* IFLA_MASTER */
		+ nla_total_size(4) /* IFLA_MTU */
		+ nla_total_size(4) /* IFLA_LINK */
		+ nla_total_size(1) /* IFLA_OPERSTATE */
		+ nla_total_size(br_port_info_size()) /* IFLA_PROTINFO */
		+ nla_total_size(br_get_link_af_size_filtered(dev,
				 filter_mask)) /* IFLA_AF_SPEC */
		+ nla_total_size(4); /* IFLA_BRPORT_BACKUP_PORT */
}