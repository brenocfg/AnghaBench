#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_11__ {scalar_t__ open_mode; } ;
struct TYPE_10__ {scalar_t__ sub_path; } ;
struct TYPE_12__ {TYPE_3__ file; TYPE_2__ dir; } ;
struct TYPE_13__ {int type; scalar_t__ orig_path; TYPE_4__ u; scalar_t__ file_name; scalar_t__ _path; int /*<<< orphan*/  std; TYPE_1__* oth_handler; } ;
typedef  TYPE_5__ spl_filesystem_object ;
struct TYPE_9__ {int /*<<< orphan*/  (* dtor ) (TYPE_5__*) ;} ;

/* Variables and functions */
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int /*<<< orphan*/  efree (scalar_t__) ; 
 int /*<<< orphan*/  spl_filesystem_file_free_line (TYPE_5__*) ; 
 TYPE_5__* spl_filesystem_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_filesystem_object_free_storage(zend_object *object) /* {{{ */
{
	spl_filesystem_object *intern = spl_filesystem_from_obj(object);

	if (intern->oth_handler && intern->oth_handler->dtor) {
		intern->oth_handler->dtor(intern);
	}

	zend_object_std_dtor(&intern->std);

	if (intern->_path) {
		efree(intern->_path);
	}
	if (intern->file_name) {
		efree(intern->file_name);
	}
	switch(intern->type) {
	case SPL_FS_INFO:
		break;
	case SPL_FS_DIR:
		if (intern->u.dir.sub_path) {
			efree(intern->u.dir.sub_path);
		}
		break;
	case SPL_FS_FILE:
		if (intern->u.file.open_mode) {
			efree(intern->u.file.open_mode);
		}
		if (intern->orig_path) {
			efree(intern->orig_path);
		}
		spl_filesystem_file_free_line(intern);
		break;
	}
}