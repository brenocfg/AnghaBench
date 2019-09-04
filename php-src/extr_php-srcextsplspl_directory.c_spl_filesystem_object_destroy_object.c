#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_9__ {TYPE_6__* stream; } ;
struct TYPE_8__ {TYPE_6__* dirp; } ;
struct TYPE_10__ {TYPE_2__ file; TYPE_1__ dir; } ;
struct TYPE_11__ {int type; TYPE_3__ u; } ;
typedef  TYPE_4__ spl_filesystem_object ;
struct TYPE_12__ {int /*<<< orphan*/  is_persistent; } ;

/* Variables and functions */
#define  SPL_FS_DIR 129 
#define  SPL_FS_FILE 128 
 int /*<<< orphan*/  php_stream_close (TYPE_6__*) ; 
 int /*<<< orphan*/  php_stream_pclose (TYPE_6__*) ; 
 TYPE_4__* spl_filesystem_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_objects_destroy_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_filesystem_object_destroy_object(zend_object *object) /* {{{ */
{
	spl_filesystem_object *intern = spl_filesystem_from_obj(object);

	zend_objects_destroy_object(object);

	switch(intern->type) {
	case SPL_FS_DIR:
		if (intern->u.dir.dirp) {
			php_stream_close(intern->u.dir.dirp);
			intern->u.dir.dirp = NULL;
		}
		break;
	case SPL_FS_FILE:
		if (intern->u.file.stream) {
			/*
			if (intern->u.file.zcontext) {
			   zend_list_delref(Z_RESVAL_P(intern->zcontext));
			}
			*/
			if (!intern->u.file.stream->is_persistent) {
				php_stream_close(intern->u.file.stream);
			} else {
				php_stream_pclose(intern->u.file.stream);
			}
			intern->u.file.stream = NULL;
		}
		break;
	default:
		break;
	}
}