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
struct hash_netiface6_elem {int /*<<< orphan*/  cidr; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_netmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
hash_netiface6_data_netmask(struct hash_netiface6_elem *elem, u8 cidr)
{
	ip6_netmask(&elem->ip, cidr);
	elem->cidr = cidr;
}