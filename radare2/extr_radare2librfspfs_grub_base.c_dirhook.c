#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grub_dirhook_info {int /*<<< orphan*/  mtime; scalar_t__ dir; } ;
struct TYPE_4__ {char type; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ RFSFile ;

/* Variables and functions */
 int /*<<< orphan*/  list ; 
 TYPE_1__* r_fs_file_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int dirhook (const char *filename, const struct grub_dirhook_info *info, void *closure) {
	RFSFile *fsf = r_fs_file_new (NULL, filename);
	fsf->type = info->dir? 'd':'f';
	fsf->time = info->mtime;
	r_list_append (list, fsf);
	//info->mtimeset
	//info->case_insensitive
	//printf ("DIRFILE: %c (%d) %s\n", info->dir?'d':'f', info->mtime, filename);
	return 0;
}