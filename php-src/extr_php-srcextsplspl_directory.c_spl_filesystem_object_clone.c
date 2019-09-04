#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_12__* ce; } ;
typedef  TYPE_5__ zend_object ;
struct TYPE_20__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_21__ {int index; TYPE_1__ entry; } ;
struct TYPE_22__ {TYPE_2__ dir; } ;
struct TYPE_25__ {int type; TYPE_4__* oth_handler; int /*<<< orphan*/  oth; int /*<<< orphan*/  info_class; int /*<<< orphan*/  file_class; TYPE_3__ u; int /*<<< orphan*/  flags; void* _path; int /*<<< orphan*/  file_name_len; void* file_name; int /*<<< orphan*/  _path_len; } ;
typedef  TYPE_6__ spl_filesystem_object ;
struct TYPE_23__ {int /*<<< orphan*/  (* clone ) (TYPE_6__*,TYPE_6__*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPL_FILE_DIR_SKIPDOTS ; 
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int SPL_HAS_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 void* estrndup (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_filesystem_dir_open (TYPE_6__*,void*) ; 
 int /*<<< orphan*/  spl_filesystem_dir_read (TYPE_6__*) ; 
 TYPE_6__* spl_filesystem_from_obj (TYPE_5__*) ; 
 int /*<<< orphan*/  spl_filesystem_is_dot (int /*<<< orphan*/ ) ; 
 TYPE_5__* spl_filesystem_object_new_ex (TYPE_12__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  zend_objects_clone_members (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object *spl_filesystem_object_clone(zend_object *old_object)
{
	zend_object *new_object;
	spl_filesystem_object *intern;
	spl_filesystem_object *source;
	int index, skip_dots;

	source = spl_filesystem_from_obj(old_object);
	new_object = spl_filesystem_object_new_ex(old_object->ce);
	intern = spl_filesystem_from_obj(new_object);

	intern->flags = source->flags;

	switch (source->type) {
		case SPL_FS_INFO:
			intern->_path_len = source->_path_len;
			intern->_path = estrndup(source->_path, source->_path_len);
			intern->file_name_len = source->file_name_len;
			intern->file_name = estrndup(source->file_name, intern->file_name_len);
			break;
		case SPL_FS_DIR:
			spl_filesystem_dir_open(intern, source->_path);
			/* read until we hit the position in which we were before */
			skip_dots = SPL_HAS_FLAG(source->flags, SPL_FILE_DIR_SKIPDOTS);
			for(index = 0; index < source->u.dir.index; ++index) {
				do {
					spl_filesystem_dir_read(intern);
				} while (skip_dots && spl_filesystem_is_dot(intern->u.dir.entry.d_name));
			}
			intern->u.dir.index = index;
			break;
		case SPL_FS_FILE:
			zend_throw_error(NULL, "An object of class %s cannot be cloned", ZSTR_VAL(old_object->ce->name));
			return new_object;
	}

	intern->file_class = source->file_class;
	intern->info_class = source->info_class;
	intern->oth = source->oth;
	intern->oth_handler = source->oth_handler;

	zend_objects_clone_members(new_object, old_object);

	if (intern->oth_handler && intern->oth_handler->clone) {
		intern->oth_handler->clone(source, intern);
	}

	return new_object;
}