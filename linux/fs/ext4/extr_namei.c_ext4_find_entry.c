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
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct buffer_head* ERR_PTR (int) ; 
 struct buffer_head* __ext4_find_entry (struct inode*,struct ext4_filename*,struct ext4_dir_entry_2**,int*) ; 
 int /*<<< orphan*/  ext4_fname_free_filename (struct ext4_filename*) ; 
 int ext4_fname_setup_filename (struct inode*,struct qstr const*,int,struct ext4_filename*) ; 

__attribute__((used)) static struct buffer_head *ext4_find_entry(struct inode *dir,
					   const struct qstr *d_name,
					   struct ext4_dir_entry_2 **res_dir,
					   int *inlined)
{
	int err;
	struct ext4_filename fname;
	struct buffer_head *bh;

	err = ext4_fname_setup_filename(dir, d_name, 1, &fname);
	if (err == -ENOENT)
		return NULL;
	if (err)
		return ERR_PTR(err);

	bh = __ext4_find_entry(dir, &fname, res_dir, inlined);

	ext4_fname_free_filename(&fname);
	return bh;
}