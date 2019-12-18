#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; unsigned int s_blocksize_bits; } ;
struct object_info {int /*<<< orphan*/  indaddr; } ;
struct TYPE_5__ {scalar_t__ endmasseq; char endname; int dircheckbyte; } ;
struct TYPE_6__ {scalar_t__ startmasseq; TYPE_1__ new; int /*<<< orphan*/  startname; } ;
struct adfs_dir {int nr_buffers; struct super_block* sb; TYPE_3__** bh; TYPE_2__ dirtail; TYPE_2__ dirhead; } ;
struct TYPE_7__ {int* b_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __adfs_dir_put (struct adfs_dir*,int,struct object_info*) ; 
 int adfs_dir_checkbyte (struct adfs_dir*) ; 
 int adfs_dir_find_entry (struct adfs_dir*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adfs_error (struct super_block*,char*) ; 
 int /*<<< orphan*/  bufoff (TYPE_3__**,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (TYPE_3__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
adfs_f_update(struct adfs_dir *dir, struct object_info *obj)
{
	struct super_block *sb = dir->sb;
	int ret, i;

	ret = adfs_dir_find_entry(dir, obj->indaddr);
	if (ret < 0) {
		adfs_error(dir->sb, "unable to locate entry to update");
		goto out;
	}

	__adfs_dir_put(dir, ret, obj);
 
	/*
	 * Increment directory sequence number
	 */
	dir->bh[0]->b_data[0] += 1;
	dir->bh[dir->nr_buffers - 1]->b_data[sb->s_blocksize - 6] += 1;

	ret = adfs_dir_checkbyte(dir);
	/*
	 * Update directory check byte
	 */
	dir->bh[dir->nr_buffers - 1]->b_data[sb->s_blocksize - 1] = ret;

#if 1
	{
	const unsigned int blocksize_bits = sb->s_blocksize_bits;

	memcpy(&dir->dirhead, bufoff(dir->bh, 0), sizeof(dir->dirhead));
	memcpy(&dir->dirtail, bufoff(dir->bh, 2007), sizeof(dir->dirtail));

	if (dir->dirhead.startmasseq != dir->dirtail.new.endmasseq ||
	    memcmp(&dir->dirhead.startname, &dir->dirtail.new.endname, 4))
		goto bad_dir;

	if (memcmp(&dir->dirhead.startname, "Nick", 4) &&
	    memcmp(&dir->dirhead.startname, "Hugo", 4))
		goto bad_dir;

	if (adfs_dir_checkbyte(dir) != dir->dirtail.new.dircheckbyte)
		goto bad_dir;
	}
#endif
	for (i = dir->nr_buffers - 1; i >= 0; i--)
		mark_buffer_dirty(dir->bh[i]);

	ret = 0;
out:
	return ret;
#if 1
bad_dir:
	adfs_error(dir->sb, "whoops!  I broke a directory!");
	return -EIO;
#endif
}