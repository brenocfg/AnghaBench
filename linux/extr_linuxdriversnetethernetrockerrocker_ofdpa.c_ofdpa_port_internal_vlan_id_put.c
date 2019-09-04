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
struct ofdpa_internal_vlan_tbl_entry {scalar_t__ ref_count; int /*<<< orphan*/  entry; int /*<<< orphan*/  vlan_id; } ;
struct ofdpa {int /*<<< orphan*/  internal_vlan_tbl_lock; int /*<<< orphan*/  internal_vlan_bitmap; } ;

/* Variables and functions */
 unsigned long OFDPA_INTERNAL_VLAN_ID_BASE ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_internal_vlan_tbl_entry*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long ntohs (int /*<<< orphan*/ ) ; 
 struct ofdpa_internal_vlan_tbl_entry* ofdpa_internal_vlan_tbl_find (struct ofdpa*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ofdpa_port_internal_vlan_id_put(const struct ofdpa_port *ofdpa_port,
				int ifindex)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_internal_vlan_tbl_entry *found;
	unsigned long lock_flags;
	unsigned long bit;

	spin_lock_irqsave(&ofdpa->internal_vlan_tbl_lock, lock_flags);

	found = ofdpa_internal_vlan_tbl_find(ofdpa, ifindex);
	if (!found) {
		netdev_err(ofdpa_port->dev,
			   "ifindex (%d) not found in internal VLAN tbl\n",
			   ifindex);
		goto not_found;
	}

	if (--found->ref_count <= 0) {
		bit = ntohs(found->vlan_id) - OFDPA_INTERNAL_VLAN_ID_BASE;
		clear_bit(bit, ofdpa->internal_vlan_bitmap);
		hash_del(&found->entry);
		kfree(found);
	}

not_found:
	spin_unlock_irqrestore(&ofdpa->internal_vlan_tbl_lock, lock_flags);
}