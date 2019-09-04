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
struct TYPE_3__ {void* k_objectid; void* k_dir_id; } ;
struct item_head {TYPE_1__ ih_key; } ;
struct TYPE_4__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct cpu_key {TYPE_2__ on_disk_key; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ih_entry_count (struct item_head*,int) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head*,int) ; 
 int /*<<< orphan*/  put_ih_version (struct item_head*,int) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_ih_k_type (struct item_head*,int) ; 

inline void make_le_item_head(struct item_head *ih, const struct cpu_key *key,
			      int version,
			      loff_t offset, int type, int length,
			      int entry_count /*or ih_free_space */ )
{
	if (key) {
		ih->ih_key.k_dir_id = cpu_to_le32(key->on_disk_key.k_dir_id);
		ih->ih_key.k_objectid =
		    cpu_to_le32(key->on_disk_key.k_objectid);
	}
	put_ih_version(ih, version);
	set_le_ih_k_offset(ih, offset);
	set_le_ih_k_type(ih, type);
	put_ih_item_len(ih, length);
	/*    set_ih_free_space (ih, 0); */
	/*
	 * for directory items it is entry count, for directs and stat
	 * datas - 0xffff, for indirects - 0
	 */
	put_ih_entry_count(ih, entry_count);
}