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
struct net_device {int dummy; } ;
struct neighbour {int dummy; } ;
struct neigh_table {int dummy; } ;

/* Variables and functions */
 struct neighbour* ___neigh_create (struct neigh_table*,void const*,struct net_device*,int,int) ; 

struct neighbour *__neigh_create(struct neigh_table *tbl, const void *pkey,
				 struct net_device *dev, bool want_ref)
{
	return ___neigh_create(tbl, pkey, dev, false, want_ref);
}