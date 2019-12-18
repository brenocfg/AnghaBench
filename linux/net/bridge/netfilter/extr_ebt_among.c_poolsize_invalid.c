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
struct ebt_mac_wormhash_tuple {int dummy; } ;
struct ebt_mac_wormhash {int poolsize; } ;

/* Variables and functions */
 int INT_MAX ; 

__attribute__((used)) static bool poolsize_invalid(const struct ebt_mac_wormhash *w)
{
	return w && w->poolsize >= (INT_MAX / sizeof(struct ebt_mac_wormhash_tuple));
}