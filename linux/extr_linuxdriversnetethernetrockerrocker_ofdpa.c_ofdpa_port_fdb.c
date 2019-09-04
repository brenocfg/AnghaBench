#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ofdpa_port {struct ofdpa* ofdpa; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  addr; struct ofdpa_port* ofdpa_port; } ;
struct ofdpa_fdb_tbl_entry {int learned; int /*<<< orphan*/  key_crc32; int /*<<< orphan*/  entry; void* touched; TYPE_1__ key; } ;
struct ofdpa {int /*<<< orphan*/  fdb_tbl_lock; int /*<<< orphan*/  fdb_tbl; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OFDPA_OP_FLAG_LEARNED ; 
 int OFDPA_OP_FLAG_REFRESH ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree (struct ofdpa_fdb_tbl_entry*) ; 
 struct ofdpa_fdb_tbl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ofdpa_fdb_tbl_entry* ofdpa_fdb_tbl_find (struct ofdpa*,struct ofdpa_fdb_tbl_entry*) ; 
 int ofdpa_port_fdb_learn (struct ofdpa_port*,int,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ofdpa_port_fdb(struct ofdpa_port *ofdpa_port,
			  const unsigned char *addr,
			  __be16 vlan_id, int flags)
{
	struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	struct ofdpa_fdb_tbl_entry *fdb;
	struct ofdpa_fdb_tbl_entry *found;
	bool removing = (flags & OFDPA_OP_FLAG_REMOVE);
	unsigned long lock_flags;

	fdb = kzalloc(sizeof(*fdb), GFP_KERNEL);
	if (!fdb)
		return -ENOMEM;

	fdb->learned = (flags & OFDPA_OP_FLAG_LEARNED);
	fdb->touched = jiffies;
	fdb->key.ofdpa_port = ofdpa_port;
	ether_addr_copy(fdb->key.addr, addr);
	fdb->key.vlan_id = vlan_id;
	fdb->key_crc32 = crc32(~0, &fdb->key, sizeof(fdb->key));

	spin_lock_irqsave(&ofdpa->fdb_tbl_lock, lock_flags);

	found = ofdpa_fdb_tbl_find(ofdpa, fdb);

	if (found) {
		found->touched = jiffies;
		if (removing) {
			kfree(fdb);
			hash_del(&found->entry);
		}
	} else if (!removing) {
		hash_add(ofdpa->fdb_tbl, &fdb->entry,
			 fdb->key_crc32);
	}

	spin_unlock_irqrestore(&ofdpa->fdb_tbl_lock, lock_flags);

	/* Check if adding and already exists, or removing and can't find */
	if (!found != !removing) {
		kfree(fdb);
		if (!found && removing)
			return 0;
		/* Refreshing existing to update aging timers */
		flags |= OFDPA_OP_FLAG_REFRESH;
	}

	return ofdpa_port_fdb_learn(ofdpa_port, flags, addr, vlan_id);
}