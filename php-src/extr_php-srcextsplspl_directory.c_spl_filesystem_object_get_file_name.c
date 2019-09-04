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
struct TYPE_7__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_8__ {TYPE_1__ entry; } ;
struct TYPE_9__ {TYPE_2__ dir; } ;
struct TYPE_10__ {int type; TYPE_3__ u; int /*<<< orphan*/  file_name; void* file_name_len; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ spl_filesystem_object ;

/* Variables and functions */
 char DEFAULT_SLASH ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  SPL_FILE_DIR_UNIXPATHS ; 
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 scalar_t__ SPL_HAS_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* spl_filesystem_object_get_path (TYPE_4__*,size_t*) ; 
 void* spprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static inline void spl_filesystem_object_get_file_name(spl_filesystem_object *intern) /* {{{ */
{
	char slash = SPL_HAS_FLAG(intern->flags, SPL_FILE_DIR_UNIXPATHS) ? '/' : DEFAULT_SLASH;

	switch (intern->type) {
		case SPL_FS_INFO:
		case SPL_FS_FILE:
			if (!intern->file_name) {
				php_error_docref(NULL, E_ERROR, "Object not initialized");
			}
			break;
		case SPL_FS_DIR:
			{
				size_t path_len = 0;
				char *path = spl_filesystem_object_get_path(intern, &path_len);
				if (intern->file_name) {
					efree(intern->file_name);
				}
				/* if there is parent path, ammend it, otherwise just use the given path as is */
				if (path_len == 0) {
					intern->file_name_len = spprintf(
						&intern->file_name, 0, "%s", intern->u.dir.entry.d_name);
				} else {
					intern->file_name_len = spprintf(
						&intern->file_name, 0, "%s%c%s", path, slash, intern->u.dir.entry.d_name);
				}
			}
			break;
	}
}