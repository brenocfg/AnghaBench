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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int ext4_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ext4_dir_entry_2*,struct buffer_head*) ; 
 struct buffer_head* ext4_find_entry (struct inode*,struct qstr const*,struct ext4_dir_entry_2**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_find_delete_entry(handle_t *handle, struct inode *dir,
				  const struct qstr *d_name)
{
	int retval = -ENOENT;
	struct buffer_head *bh;
	struct ext4_dir_entry_2 *de;

	bh = ext4_find_entry(dir, d_name, &de, NULL);
	if (IS_ERR(bh))
		return PTR_ERR(bh);
	if (bh) {
		retval = ext4_delete_entry(handle, dir, de, bh);
		brelse(bh);
	}
	return retval;
}