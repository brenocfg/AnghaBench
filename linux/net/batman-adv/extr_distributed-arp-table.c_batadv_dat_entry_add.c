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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct batadv_priv {TYPE_1__ dat; } ;
struct batadv_dat_entry {unsigned short vid; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ip; int /*<<< orphan*/  hash_entry; int /*<<< orphan*/  refcount; void* last_update; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_DAT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  batadv_compare_dat ; 
 int /*<<< orphan*/  batadv_compare_eth (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct batadv_dat_entry* batadv_dat_entry_hash_find (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_put (struct batadv_dat_entry*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int batadv_hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct batadv_dat_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_hash_dat ; 
 int /*<<< orphan*/  batadv_print_vid (unsigned short) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 struct batadv_dat_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void batadv_dat_entry_add(struct batadv_priv *bat_priv, __be32 ip,
				 u8 *mac_addr, unsigned short vid)
{
	struct batadv_dat_entry *dat_entry;
	int hash_added;

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip, vid);
	/* if this entry is already known, just update it */
	if (dat_entry) {
		if (!batadv_compare_eth(dat_entry->mac_addr, mac_addr))
			ether_addr_copy(dat_entry->mac_addr, mac_addr);
		dat_entry->last_update = jiffies;
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "Entry updated: %pI4 %pM (vid: %d)\n",
			   &dat_entry->ip, dat_entry->mac_addr,
			   batadv_print_vid(vid));
		goto out;
	}

	dat_entry = kmalloc(sizeof(*dat_entry), GFP_ATOMIC);
	if (!dat_entry)
		goto out;

	dat_entry->ip = ip;
	dat_entry->vid = vid;
	ether_addr_copy(dat_entry->mac_addr, mac_addr);
	dat_entry->last_update = jiffies;
	kref_init(&dat_entry->refcount);

	kref_get(&dat_entry->refcount);
	hash_added = batadv_hash_add(bat_priv->dat.hash, batadv_compare_dat,
				     batadv_hash_dat, dat_entry,
				     &dat_entry->hash_entry);

	if (unlikely(hash_added != 0)) {
		/* remove the reference for the hash */
		batadv_dat_entry_put(dat_entry);
		goto out;
	}

	batadv_dbg(BATADV_DBG_DAT, bat_priv, "New entry added: %pI4 %pM (vid: %d)\n",
		   &dat_entry->ip, dat_entry->mac_addr, batadv_print_vid(vid));

out:
	if (dat_entry)
		batadv_dat_entry_put(dat_entry);
}