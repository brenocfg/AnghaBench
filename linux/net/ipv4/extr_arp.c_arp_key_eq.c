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
struct neighbour {int dummy; } ;

/* Variables and functions */
 int neigh_key_eq32 (struct neighbour const*,void const*) ; 

__attribute__((used)) static bool arp_key_eq(const struct neighbour *neigh, const void *pkey)
{
	return neigh_key_eq32(neigh, pkey);
}