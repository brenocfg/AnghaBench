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

/* Variables and functions */
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPV6_HOPOPTS ; 
 int IP_OPTIONS ; 

__attribute__((used)) static inline int selinux_netlbl_option(int level, int optname)
{
	return (level == IPPROTO_IP && optname == IP_OPTIONS) ||
		(level == IPPROTO_IPV6 && optname == IPV6_HOPOPTS);
}