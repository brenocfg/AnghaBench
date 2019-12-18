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
struct msdos_dir_entry {int /*<<< orphan*/  name; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 scalar_t__ fat_get_short_entry (struct inode*,int /*<<< orphan*/ *,struct buffer_head**,struct msdos_dir_entry**) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fat_get_dotdot_entry(struct inode *dir, struct buffer_head **bh,
			 struct msdos_dir_entry **de)
{
	loff_t offset = 0;

	*de = NULL;
	while (fat_get_short_entry(dir, &offset, bh, de) >= 0) {
		if (!strncmp((*de)->name, MSDOS_DOTDOT, MSDOS_NAME))
			return 0;
	}
	return -ENOENT;
}