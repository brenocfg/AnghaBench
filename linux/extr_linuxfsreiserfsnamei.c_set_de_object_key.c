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
struct reiserfs_dir_entry {size_t de_entry_num; int /*<<< orphan*/ * de_deh; int /*<<< orphan*/  de_objectid; int /*<<< orphan*/  de_dir_id; int /*<<< orphan*/  de_ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  deh_dir_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deh_objectid (int /*<<< orphan*/ *) ; 
 size_t ih_entry_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_de_object_key(struct reiserfs_dir_entry *de)
{
	BUG_ON(de->de_entry_num >= ih_entry_count(de->de_ih));
	de->de_dir_id = deh_dir_id(&de->de_deh[de->de_entry_num]);
	de->de_objectid = deh_objectid(&de->de_deh[de->de_entry_num]);
}