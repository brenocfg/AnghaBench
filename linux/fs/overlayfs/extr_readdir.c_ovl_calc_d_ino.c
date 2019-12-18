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
struct ovl_readdir_data {TYPE_1__* dentry; int /*<<< orphan*/  is_upper; } ;
struct ovl_cache_entry {char* name; int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_IMPURE ; 
 int /*<<< orphan*/  d_inode (TYPE_1__*) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_xino_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool ovl_calc_d_ino(struct ovl_readdir_data *rdd,
			   struct ovl_cache_entry *p)
{
	/* Don't care if not doing ovl_iter() */
	if (!rdd->dentry)
		return false;

	/* Always recalc d_ino when remapping lower inode numbers */
	if (ovl_xino_bits(rdd->dentry->d_sb))
		return true;

	/* Always recalc d_ino for parent */
	if (strcmp(p->name, "..") == 0)
		return true;

	/* If this is lower, then native d_ino will do */
	if (!rdd->is_upper)
		return false;

	/*
	 * Recalc d_ino for '.' and for all entries if dir is impure (contains
	 * copied up entries)
	 */
	if ((p->name[0] == '.' && p->len == 1) ||
	    ovl_test_flag(OVL_IMPURE, d_inode(rdd->dentry)))
		return true;

	return false;
}