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
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void br_mdb_hash_fini(struct net_bridge *br)
{
	rhashtable_destroy(&br->mdb_hash_tbl);
}