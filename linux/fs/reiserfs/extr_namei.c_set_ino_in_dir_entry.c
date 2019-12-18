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
struct reiserfs_key {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct reiserfs_dir_entry {size_t de_entry_num; TYPE_1__* de_deh; } ;
struct TYPE_2__ {int /*<<< orphan*/  deh_objectid; int /*<<< orphan*/  deh_dir_id; } ;

/* Variables and functions */

__attribute__((used)) static void set_ino_in_dir_entry(struct reiserfs_dir_entry *de,
				 struct reiserfs_key *key)
{
	/* JDM These operations are endian safe - both are le */
	de->de_deh[de->de_entry_num].deh_dir_id = key->k_dir_id;
	de->de_deh[de->de_entry_num].deh_objectid = key->k_objectid;
}