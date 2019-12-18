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
struct netdev_hw_addr_list {int dummy; } ;

/* Variables and functions */
 int __hw_addr_del_ex (struct netdev_hw_addr_list*,unsigned char const*,int,unsigned char,int,int) ; 

__attribute__((used)) static int __hw_addr_del(struct netdev_hw_addr_list *list,
			 const unsigned char *addr, int addr_len,
			 unsigned char addr_type)
{
	return __hw_addr_del_ex(list, addr, addr_len, addr_type, false, false);
}