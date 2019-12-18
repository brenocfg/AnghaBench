#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mt7530_priv {TYPE_2__* vlan_entries; TYPE_1__* port_entries; } ;
struct mt7530_mapping {int /*<<< orphan*/ * vids; int /*<<< orphan*/ * etags; int /*<<< orphan*/ * members; int /*<<< orphan*/ * pvids; } ;
struct TYPE_4__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  etags; int /*<<< orphan*/  member; } ;
struct TYPE_3__ {int /*<<< orphan*/  pvid; } ;

/* Variables and functions */
 int MT7530_NUM_PORTS ; 
 int MT7530_NUM_VLANS ; 

__attribute__((used)) static void
mt7530_apply_mapping(struct mt7530_priv *mt7530, struct mt7530_mapping *map)
{
	int i = 0;

	for (i = 0; i < MT7530_NUM_PORTS; i++)
		mt7530->port_entries[i].pvid = map->pvids[i];

	for (i = 0; i < MT7530_NUM_VLANS; i++) {
		mt7530->vlan_entries[i].member = map->members[i];
		mt7530->vlan_entries[i].etags = map->etags[i];
		mt7530->vlan_entries[i].vid = map->vids[i];
	}
}