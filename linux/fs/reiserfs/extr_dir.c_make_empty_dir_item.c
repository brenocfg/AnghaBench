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
struct reiserfs_de_head {scalar_t__ deh_state; void* deh_objectid; void* deh_dir_id; } ;
typedef  void* __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_DOT_OFFSET ; 
 int /*<<< orphan*/  DOT_OFFSET ; 
 int EMPTY_DIR_SIZE ; 
 int ROUND_UP (int /*<<< orphan*/ ) ; 
 int deh_location (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  mark_de_visible (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_deh_location (struct reiserfs_de_head*,int) ; 
 int /*<<< orphan*/  put_deh_offset (struct reiserfs_de_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void make_empty_dir_item(char *body, __le32 dirid, __le32 objid,
			 __le32 par_dirid, __le32 par_objid)
{
	struct reiserfs_de_head *dot, *dotdot;

	memset(body, 0, EMPTY_DIR_SIZE);
	dot = (struct reiserfs_de_head *)body;
	dotdot = dot + 1;

	/* direntry header of "." */
	put_deh_offset(dot, DOT_OFFSET);
	/* these two are from make_le_item_head, and are are LE */
	dot->deh_dir_id = dirid;
	dot->deh_objectid = objid;
	dot->deh_state = 0;	/* Endian safe if 0 */
	put_deh_location(dot, EMPTY_DIR_SIZE - ROUND_UP(strlen(".")));
	mark_de_visible(dot);

	/* direntry header of ".." */
	put_deh_offset(dotdot, DOT_DOT_OFFSET);
	/* key of ".." for the root directory */
	/* these two are from the inode, and are are LE */
	dotdot->deh_dir_id = par_dirid;
	dotdot->deh_objectid = par_objid;
	dotdot->deh_state = 0;	/* Endian safe if 0 */
	put_deh_location(dotdot, deh_location(dot) - ROUND_UP(strlen("..")));
	mark_de_visible(dotdot);

	/* copy ".." and "." */
	memcpy(body + deh_location(dot), ".", 1);
	memcpy(body + deh_location(dotdot), "..", 2);
}