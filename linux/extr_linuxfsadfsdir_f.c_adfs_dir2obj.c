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
struct object_info {size_t name_len; int loadaddr; int attr; int filetype; int /*<<< orphan*/ * name; void* size; void* execaddr; void* file_id; } ;
struct adfs_direntry {int newdiratts; int /*<<< orphan*/  dirlen; int /*<<< orphan*/  direxec; int /*<<< orphan*/  dirload; int /*<<< orphan*/  dirinddiscadd; int /*<<< orphan*/  dirobname; } ;
struct adfs_dir {int /*<<< orphan*/  sb; } ;
typedef  int __u16 ;
struct TYPE_2__ {scalar_t__ s_ftsuffix; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADFS_F_NAME_LEN ; 
 int ADFS_NDA_DIRECTORY ; 
 TYPE_1__* ADFS_SB (int /*<<< orphan*/ ) ; 
 size_t adfs_readname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* adfs_readval (int /*<<< orphan*/ ,int) ; 
 scalar_t__ append_filetype_suffix (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
adfs_dir2obj(struct adfs_dir *dir, struct object_info *obj,
	struct adfs_direntry *de)
{
	obj->name_len =	adfs_readname(obj->name, de->dirobname, ADFS_F_NAME_LEN);
	obj->file_id  = adfs_readval(de->dirinddiscadd, 3);
	obj->loadaddr = adfs_readval(de->dirload, 4);
	obj->execaddr = adfs_readval(de->direxec, 4);
	obj->size     = adfs_readval(de->dirlen,  4);
	obj->attr     = de->newdiratts;
	obj->filetype = -1;

	/*
	 * object is a file and is filetyped and timestamped?
	 * RISC OS 12-bit filetype is stored in load_address[19:8]
	 */
	if ((0 == (obj->attr & ADFS_NDA_DIRECTORY)) &&
		(0xfff00000 == (0xfff00000 & obj->loadaddr))) {
		obj->filetype = (__u16) ((0x000fff00 & obj->loadaddr) >> 8);

		/* optionally append the ,xyz hex filetype suffix */
		if (ADFS_SB(dir->sb)->s_ftsuffix)
			obj->name_len +=
				append_filetype_suffix(
					&obj->name[obj->name_len],
					obj->filetype);
	}
}