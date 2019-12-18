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
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_super_block {int dummy; } ;
struct squashfs_sb_info {int dummy; } ;
typedef  void squashfs_page_actor ;

/* Variables and functions */
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ SQUASHFS_COMP_OPTS (unsigned short) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* squashfs_comp_opts (struct squashfs_sb_info*,void*,int) ; 
 void* squashfs_page_actor_init (void**,int,int /*<<< orphan*/ ) ; 
 int squashfs_read_data (struct super_block*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void *get_comp_opts(struct super_block *sb, unsigned short flags)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	void *buffer = NULL, *comp_opts;
	struct squashfs_page_actor *actor = NULL;
	int length = 0;

	/*
	 * Read decompressor specific options from file system if present
	 */
	if (SQUASHFS_COMP_OPTS(flags)) {
		buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
		if (buffer == NULL) {
			comp_opts = ERR_PTR(-ENOMEM);
			goto out;
		}

		actor = squashfs_page_actor_init(&buffer, 1, 0);
		if (actor == NULL) {
			comp_opts = ERR_PTR(-ENOMEM);
			goto out;
		}

		length = squashfs_read_data(sb,
			sizeof(struct squashfs_super_block), 0, NULL, actor);

		if (length < 0) {
			comp_opts = ERR_PTR(length);
			goto out;
		}
	}

	comp_opts = squashfs_comp_opts(msblk, buffer, length);

out:
	kfree(actor);
	kfree(buffer);
	return comp_opts;
}