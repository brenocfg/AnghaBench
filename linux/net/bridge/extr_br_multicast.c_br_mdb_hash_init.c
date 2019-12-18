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
struct net_bridge {int /*<<< orphan*/  mdb_hash_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_mdb_rht_params ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int br_mdb_hash_init(struct net_bridge *br)
{
	return rhashtable_init(&br->mdb_hash_tbl, &br_mdb_rht_params);
}