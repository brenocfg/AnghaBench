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
typedef  int u16 ;
struct object_info {unsigned int name_len; char* name; int attr; int /*<<< orphan*/  loadaddr; } ;
struct adfs_dir {int /*<<< orphan*/  sb; } ;
struct TYPE_2__ {scalar_t__ s_ftsuffix; } ;

/* Variables and functions */
 int ADFS_FILETYPE_NONE ; 
 int ADFS_NDA_DIRECTORY ; 
 TYPE_1__* ADFS_SB (int /*<<< orphan*/ ) ; 
 int adfs_filetype (int /*<<< orphan*/ ) ; 
 void* hex_asc_lo (int) ; 

void adfs_object_fixup(struct adfs_dir *dir, struct object_info *obj)
{
	unsigned int dots, i;

	/*
	 * RISC OS allows the use of '/' in directory entry names, so we need
	 * to fix these up.  '/' is typically used for FAT compatibility to
	 * represent '.', so do the same conversion here.  In any case, '.'
	 * will never be in a RISC OS name since it is used as the pathname
	 * separator.  Handle the case where we may generate a '.' or '..'
	 * name, replacing the first character with '^' (the RISC OS "parent
	 * directory" character.)
	 */
	for (i = dots = 0; i < obj->name_len; i++)
		if (obj->name[i] == '/') {
			obj->name[i] = '.';
			dots++;
		}

	if (obj->name_len <= 2 && dots == obj->name_len)
		obj->name[0] = '^';

	/*
	 * If the object is a file, and the user requested the ,xyz hex
	 * filetype suffix to the name, check the filetype and append.
	 */
	if (!(obj->attr & ADFS_NDA_DIRECTORY) && ADFS_SB(dir->sb)->s_ftsuffix) {
		u16 filetype = adfs_filetype(obj->loadaddr);

		if (filetype != ADFS_FILETYPE_NONE) {
			obj->name[obj->name_len++] = ',';
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 8);
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 4);
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 0);
		}
	}
}