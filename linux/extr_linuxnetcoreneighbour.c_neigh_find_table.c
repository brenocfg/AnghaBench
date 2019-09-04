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
struct neigh_table {int dummy; } ;

/* Variables and functions */
#define  AF_DECnet 130 
#define  AF_INET 129 
#define  AF_INET6 128 
 size_t NEIGH_ARP_TABLE ; 
 size_t NEIGH_DN_TABLE ; 
 size_t NEIGH_ND_TABLE ; 
 struct neigh_table** neigh_tables ; 

__attribute__((used)) static struct neigh_table *neigh_find_table(int family)
{
	struct neigh_table *tbl = NULL;

	switch (family) {
	case AF_INET:
		tbl = neigh_tables[NEIGH_ARP_TABLE];
		break;
	case AF_INET6:
		tbl = neigh_tables[NEIGH_ND_TABLE];
		break;
	case AF_DECnet:
		tbl = neigh_tables[NEIGH_DN_TABLE];
		break;
	}

	return tbl;
}