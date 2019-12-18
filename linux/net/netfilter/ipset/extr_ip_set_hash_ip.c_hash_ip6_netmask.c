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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_netmask (union nf_inet_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
hash_ip6_netmask(union nf_inet_addr *ip, u8 prefix)
{
	ip6_netmask(ip, prefix);
}