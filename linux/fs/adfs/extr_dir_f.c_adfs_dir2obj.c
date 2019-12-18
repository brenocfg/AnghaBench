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
struct object_info {char* name; unsigned int name_len; int /*<<< orphan*/  attr; void* size; void* execaddr; void* loadaddr; void* indaddr; } ;
struct adfs_direntry {char* dirobname; int /*<<< orphan*/  newdiratts; int /*<<< orphan*/  dirlen; int /*<<< orphan*/  direxec; int /*<<< orphan*/  dirload; int /*<<< orphan*/  dirinddiscadd; } ;
struct adfs_dir {int dummy; } ;

/* Variables and functions */
 unsigned int ADFS_F_NAME_LEN ; 
 int /*<<< orphan*/  adfs_object_fixup (struct adfs_dir*,struct object_info*) ; 
 void* adfs_readval (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
adfs_dir2obj(struct adfs_dir *dir, struct object_info *obj,
	struct adfs_direntry *de)
{
	unsigned int name_len;

	for (name_len = 0; name_len < ADFS_F_NAME_LEN; name_len++) {
		if (de->dirobname[name_len] < ' ')
			break;

		obj->name[name_len] = de->dirobname[name_len];
	}

	obj->name_len =	name_len;
	obj->indaddr  = adfs_readval(de->dirinddiscadd, 3);
	obj->loadaddr = adfs_readval(de->dirload, 4);
	obj->execaddr = adfs_readval(de->direxec, 4);
	obj->size     = adfs_readval(de->dirlen,  4);
	obj->attr     = de->newdiratts;

	adfs_object_fixup(dir, obj);
}