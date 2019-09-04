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
struct inetpeer_addr {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_METRICS_ATTR_ADDR_IPV4 ; 
 int /*<<< orphan*/  TCP_METRICS_ATTR_ADDR_IPV6 ; 
 int __parse_nl_addr (struct genl_info*,struct inetpeer_addr*,unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_nl_addr(struct genl_info *info, struct inetpeer_addr *addr,
			 unsigned int *hash, int optional)
{
	return __parse_nl_addr(info, addr, hash, optional,
			       TCP_METRICS_ATTR_ADDR_IPV4,
			       TCP_METRICS_ATTR_ADDR_IPV6);
}