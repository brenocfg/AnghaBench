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
struct key {int dummy; } ;
struct afs_vldb_entry {int dummy; } ;
struct afs_vl_cursor {int dummy; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int ERESTARTSYS ; 
 struct afs_vldb_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  afs_begin_vlserver_operation (struct afs_vl_cursor*,struct afs_cell*,struct key*) ; 
 int afs_end_vlserver_operation (struct afs_vl_cursor*) ; 
 scalar_t__ afs_select_vlserver (struct afs_vl_cursor*) ; 
 struct afs_vldb_entry* afs_vl_get_entry_by_name_u (struct afs_vl_cursor*,char const*,size_t) ; 

__attribute__((used)) static struct afs_vldb_entry *afs_vl_lookup_vldb(struct afs_cell *cell,
						 struct key *key,
						 const char *volname,
						 size_t volnamesz)
{
	struct afs_vldb_entry *vldb = ERR_PTR(-EDESTADDRREQ);
	struct afs_vl_cursor vc;
	int ret;

	if (!afs_begin_vlserver_operation(&vc, cell, key))
		return ERR_PTR(-ERESTARTSYS);

	while (afs_select_vlserver(&vc)) {
		vldb = afs_vl_get_entry_by_name_u(&vc, volname, volnamesz);
	}

	ret = afs_end_vlserver_operation(&vc);
	return ret < 0 ? ERR_PTR(ret) : vldb;
}