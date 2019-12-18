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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct ifinfomsg {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int MAX_ADDR_LEN ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t bridge_nlmsg_size(void)
{
	return NLMSG_ALIGN(sizeof(struct ifinfomsg))
		+ nla_total_size(IFNAMSIZ)	/* IFLA_IFNAME */
		+ nla_total_size(MAX_ADDR_LEN)	/* IFLA_ADDRESS */
		+ nla_total_size(sizeof(u32))	/* IFLA_MASTER */
		+ nla_total_size(sizeof(u32))	/* IFLA_MTU */
		+ nla_total_size(sizeof(u32))	/* IFLA_LINK */
		+ nla_total_size(sizeof(u32))	/* IFLA_OPERSTATE */
		+ nla_total_size(sizeof(u8))	/* IFLA_PROTINFO */
		+ nla_total_size(sizeof(struct nlattr))	/* IFLA_AF_SPEC */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRIDGE_FLAGS */
		+ nla_total_size(sizeof(u16));	/* IFLA_BRIDGE_MODE */
}