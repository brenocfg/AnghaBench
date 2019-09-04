#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * d_name; } ;
struct TYPE_8__ {TYPE_1__ entry; } ;
struct TYPE_9__ {TYPE_2__ dir; } ;
struct TYPE_10__ {int type; size_t file_name_len; char* file_name; TYPE_3__ u; } ;
typedef  TYPE_4__ spl_filesystem_object ;

/* Variables and functions */
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int /*<<< orphan*/  spl_filesystem_object_get_file_name (TYPE_4__*) ; 

__attribute__((used)) static char *spl_filesystem_object_get_pathname(spl_filesystem_object *intern, size_t *len) { /* {{{ */
	switch (intern->type) {
		case SPL_FS_INFO:
		case SPL_FS_FILE:
			*len = intern->file_name_len;
			return intern->file_name;
		case SPL_FS_DIR:
			if (intern->u.dir.entry.d_name[0]) {
				spl_filesystem_object_get_file_name(intern);
				*len = intern->file_name_len;
				return intern->file_name;
			}
	}
	*len = 0;
	return NULL;
}