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
struct treepath {int dummy; } ;
struct reiserfs_dir_entry {int /*<<< orphan*/  de_item_num; int /*<<< orphan*/  de_ih; int /*<<< orphan*/  de_bh; int /*<<< orphan*/  de_deh; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_I_DEH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_LAST_POSITION (struct treepath*) ; 
 int /*<<< orphan*/  get_last_bh (struct treepath*) ; 
 int /*<<< orphan*/  tp_item_head (struct treepath*) ; 

__attribute__((used)) static inline void set_de_item_location(struct reiserfs_dir_entry *de,
					struct treepath *path)
{
	de->de_bh = get_last_bh(path);
	de->de_ih = tp_item_head(path);
	de->de_deh = B_I_DEH(de->de_bh, de->de_ih);
	de->de_item_num = PATH_LAST_POSITION(path);
}