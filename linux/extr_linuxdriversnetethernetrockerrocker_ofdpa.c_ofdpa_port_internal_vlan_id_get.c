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
struct ofdpa_port {int /*<<< orphan*/  dev; struct ofdpa* ofdpa; } ;
struct ofdpa_internal_vlan_tbl_entry {int ifindex; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  entry; } ;
struct ofdpa {int /*<<< orphan*/  internal_vlan_tbl_lock; int /*<<< orphan*/  internal_vlan_bitmap; int /*<<< orphan*/  internal_vlan_tbl; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OFDPA_INTERNAL_VLAN_ID_BASE ; 
 int OFDPA_N_INTERNAL_VLANS ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_internal_vlan_tbl_entry*) ; 
 struct ofdpa_internal_vlan_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct ofdpa_internal_vlan_tbl_entry* ofdpa_internal_vlan_tbl_find (struct ofdpa*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 ofdpa_port_internal_vlan_id_get(struct ofdpa_port *ofdpa_port,
					      int ifindex)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_internal_vlan_tbl_entry *entry;
	struct ofdpa_internal_vlan_tbl_entry *found;
	unsigned long lock_flags;
	int i;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return 0;

	entry->ifindex = ifindex;

	spin_lock_irqsave(&ofdpa->internal_vlan_tbl_lock, lock_flags);

	found = ofdpa_internal_vlan_tbl_find(ofdpa, ifindex);
	if (found) {
		kfree(entry);
		goto found;
	}

	found = entry;
	hash_add(ofdpa->internal_vlan_tbl, &found->entry, found->ifindex);

	for (i = 0; i < OFDPA_N_INTERNAL_VLANS; i++) {
		if (test_and_set_bit(i, ofdpa->internal_vlan_bitmap))
			continue;
		found->vlan_id = htons(OFDPA_INTERNAL_VLAN_ID_BASE + i);
		goto found;
	}

	netdev_err(ofdpa_port->dev, "Out of internal VLAN IDs\n");

found:
	found->ref_count++;
	spin_unlock_irqrestore(&ofdpa->internal_vlan_tbl_lock, lock_flags);

	return found->vlan_id;
}