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
struct ceph_mds_reply_info_parsed {TYPE_1__* dir_entries; int /*<<< orphan*/  dir_nr; } ;
struct ceph_dir_file_info {scalar_t__ frag; TYPE_2__* last_readdir; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {struct ceph_mds_reply_info_parsed r_reply_info; } ;
struct TYPE_3__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ fpos_frag (scalar_t__) ; 
 scalar_t__ is_hash_order (scalar_t__) ; 

__attribute__((used)) static bool need_reset_readdir(struct ceph_dir_file_info *dfi, loff_t new_pos)
{
	struct ceph_mds_reply_info_parsed *rinfo;
	loff_t chunk_offset;
	if (new_pos == 0)
		return true;
	if (is_hash_order(new_pos)) {
		/* no need to reset last_name for a forward seek when
		 * dentries are sotred in hash order */
	} else if (dfi->frag != fpos_frag(new_pos)) {
		return true;
	}
	rinfo = dfi->last_readdir ? &dfi->last_readdir->r_reply_info : NULL;
	if (!rinfo || !rinfo->dir_nr)
		return true;
	chunk_offset = rinfo->dir_entries[0].offset;
	return new_pos < chunk_offset ||
	       is_hash_order(new_pos) != is_hash_order(chunk_offset);
}