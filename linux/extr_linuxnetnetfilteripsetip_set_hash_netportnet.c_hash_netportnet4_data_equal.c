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
struct hash_netportnet4_elem {scalar_t__ ipcmp; scalar_t__ ccmp; scalar_t__ port; scalar_t__ proto; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
hash_netportnet4_data_equal(const struct hash_netportnet4_elem *ip1,
			    const struct hash_netportnet4_elem *ip2,
			    u32 *multi)
{
	return ip1->ipcmp == ip2->ipcmp &&
	       ip1->ccmp == ip2->ccmp &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
}