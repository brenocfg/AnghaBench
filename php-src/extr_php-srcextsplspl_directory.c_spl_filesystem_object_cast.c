#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_15__ {TYPE_1__* ce; } ;
typedef  TYPE_5__ zend_object ;
struct TYPE_12__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_13__ {TYPE_2__ entry; } ;
struct TYPE_14__ {TYPE_3__ dir; } ;
struct TYPE_16__ {int type; TYPE_4__ u; int /*<<< orphan*/  file_name_len; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_6__ spl_filesystem_object ;
struct TYPE_11__ {scalar_t__ __tostring; } ;

/* Variables and functions */
 int FAILURE ; 
 int IS_STRING ; 
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int _IS_BOOL ; 
 TYPE_6__* spl_filesystem_from_obj (TYPE_5__*) ; 
 int zend_std_cast_object_tostring (TYPE_5__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int spl_filesystem_object_cast(zend_object *readobj, zval *writeobj, int type)
{
	spl_filesystem_object *intern = spl_filesystem_from_obj(readobj);

	if (type == IS_STRING) {
		if (readobj->ce->__tostring) {
			return zend_std_cast_object_tostring(readobj, writeobj, type);
		}

		switch (intern->type) {
		case SPL_FS_INFO:
		case SPL_FS_FILE:
			ZVAL_STRINGL(writeobj, intern->file_name, intern->file_name_len);
			return SUCCESS;
		case SPL_FS_DIR:
			ZVAL_STRING(writeobj, intern->u.dir.entry.d_name);
			return SUCCESS;
		}
	} else if (type == _IS_BOOL) {
		ZVAL_TRUE(writeobj);
		return SUCCESS;
	}
	ZVAL_NULL(writeobj);
	return FAILURE;
}