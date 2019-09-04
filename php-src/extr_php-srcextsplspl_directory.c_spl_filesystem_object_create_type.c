#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_error_handling ;
struct TYPE_27__ {TYPE_10__* constructor; } ;
typedef  TYPE_6__ zend_class_entry ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_25__ {char* open_mode; int open_mode_len; int /*<<< orphan*/  zcontext; } ;
struct TYPE_22__ {int /*<<< orphan*/ * d_name; } ;
struct TYPE_23__ {TYPE_1__ entry; } ;
struct TYPE_26__ {TYPE_4__ file; TYPE_2__ dir; } ;
struct TYPE_28__ {int type; char* file_name; int file_name_len; char* _path; int _path_len; TYPE_5__ u; int /*<<< orphan*/  std; TYPE_6__* file_class; TYPE_6__* info_class; } ;
typedef  TYPE_7__ spl_filesystem_object ;
struct TYPE_24__ {int /*<<< orphan*/  scope; } ;
struct TYPE_21__ {TYPE_3__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  EH_THROW ; 
 int /*<<< orphan*/  FAILURE ; 
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  UNEXPECTED (int) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 void* estrndup (char*,int) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 int /*<<< orphan*/  spl_ce_SplFileInfo ; 
 int /*<<< orphan*/  spl_ce_SplFileObject ; 
 int /*<<< orphan*/  spl_filesystem_file_open (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* spl_filesystem_from_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_filesystem_object_get_file_name (TYPE_7__*) ; 
 void* spl_filesystem_object_get_path (TYPE_7__*,int*) ; 
 int /*<<< orphan*/  spl_filesystem_object_new_ex (TYPE_6__*) ; 
 int /*<<< orphan*/  zend_call_method_with_1_params (int /*<<< orphan*/ ,TYPE_6__*,TYPE_10__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_method_with_2_params (int /*<<< orphan*/ ,TYPE_6__*,TYPE_10__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_parse_parameters (int,char*,char**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_replace_error_handling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_restore_error_handling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_update_class_constants (TYPE_6__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static spl_filesystem_object *spl_filesystem_object_create_type(int ht, spl_filesystem_object *source, int type, zend_class_entry *ce, zval *return_value) /* {{{ */
{
	spl_filesystem_object *intern;
	zend_bool use_include_path = 0;
	zval arg1, arg2;
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, spl_ce_RuntimeException, &error_handling);

	switch (source->type) {
		case SPL_FS_INFO:
		case SPL_FS_FILE:
			break;
		case SPL_FS_DIR:
			if (!source->u.dir.entry.d_name[0]) {
				zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Could not open file");
				zend_restore_error_handling(&error_handling);
				return NULL;
			}
	}

	switch (type) {
		case SPL_FS_INFO:
			ce = ce ? ce : source->info_class;

			if (UNEXPECTED(zend_update_class_constants(ce) != SUCCESS)) {
				break;
			}

			intern = spl_filesystem_from_obj(spl_filesystem_object_new_ex(ce));
			ZVAL_OBJ(return_value, &intern->std);

			spl_filesystem_object_get_file_name(source);
			if (ce->constructor->common.scope != spl_ce_SplFileInfo) {
				ZVAL_STRINGL(&arg1, source->file_name, source->file_name_len);
				zend_call_method_with_1_params(Z_OBJ_P(return_value), ce, &ce->constructor, "__construct", NULL, &arg1);
				zval_ptr_dtor(&arg1);
			} else {
				intern->file_name = estrndup(source->file_name, source->file_name_len);
				intern->file_name_len = source->file_name_len;
				intern->_path = spl_filesystem_object_get_path(source, &intern->_path_len);
				intern->_path = estrndup(intern->_path, intern->_path_len);
			}
			break;
		case SPL_FS_FILE:
			ce = ce ? ce : source->file_class;

			if (UNEXPECTED(zend_update_class_constants(ce) != SUCCESS)) {
				break;
			}

			intern = spl_filesystem_from_obj(spl_filesystem_object_new_ex(ce));

			ZVAL_OBJ(return_value, &intern->std);

			spl_filesystem_object_get_file_name(source);

			if (ce->constructor->common.scope != spl_ce_SplFileObject) {
				ZVAL_STRINGL(&arg1, source->file_name, source->file_name_len);
				ZVAL_STRINGL(&arg2, "r", 1);
				zend_call_method_with_2_params(Z_OBJ_P(return_value), ce, &ce->constructor, "__construct", NULL, &arg1, &arg2);
				zval_ptr_dtor(&arg1);
				zval_ptr_dtor(&arg2);
			} else {
				intern->file_name = source->file_name;
				intern->file_name_len = source->file_name_len;
				intern->_path = spl_filesystem_object_get_path(source, &intern->_path_len);
				intern->_path = estrndup(intern->_path, intern->_path_len);

				intern->u.file.open_mode = "r";
				intern->u.file.open_mode_len = 1;

				if (ht && zend_parse_parameters(ht, "|sbr",
							&intern->u.file.open_mode, &intern->u.file.open_mode_len,
							&use_include_path, &intern->u.file.zcontext) == FAILURE) {
					zend_restore_error_handling(&error_handling);
					intern->u.file.open_mode = NULL;
					intern->file_name = NULL;
					zval_ptr_dtor(return_value);
					ZVAL_NULL(return_value);
					return NULL;
				}

				if (spl_filesystem_file_open(intern, use_include_path, 0) == FAILURE) {
					zend_restore_error_handling(&error_handling);
					zval_ptr_dtor(return_value);
					ZVAL_NULL(return_value);
					return NULL;
				}
			}
			break;
		case SPL_FS_DIR:
			zend_restore_error_handling(&error_handling);
			zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Operation not supported");
			return NULL;
	}
	zend_restore_error_handling(&error_handling);
	return NULL;
}