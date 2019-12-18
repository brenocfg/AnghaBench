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
struct hash_ipportip4_elem {scalar_t__ ip; scalar_t__ ip2; scalar_t__ port; scalar_t__ proto; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
hash_ipportip4_data_equal(const struct hash_ipportip4_elem *ip1,
			  const struct hash_ipportip4_elem *ip2,
			  u32 *multi)
{
	return ip1->ip == ip2->ip &&
	       ip1->ip2 == ip2->ip2 &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
}