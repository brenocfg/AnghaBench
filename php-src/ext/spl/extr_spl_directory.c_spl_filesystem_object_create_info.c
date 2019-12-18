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
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_error_handling ;
struct TYPE_14__ {TYPE_6__* constructor; } ;
typedef  TYPE_2__ zend_class_entry ;
struct TYPE_15__ {int /*<<< orphan*/  std; TYPE_2__* info_class; } ;
typedef  TYPE_3__ spl_filesystem_object ;
struct TYPE_13__ {scalar_t__ scope; } ;
struct TYPE_16__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  EH_THROW ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 scalar_t__ spl_ce_SplFileInfo ; 
 TYPE_3__* spl_filesystem_from_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_filesystem_info_set_filename (TYPE_3__*,char*,size_t,int) ; 
 int /*<<< orphan*/  spl_filesystem_object_new_ex (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_call_method_with_1_params (int /*<<< orphan*/ ,TYPE_2__*,TYPE_6__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_replace_error_handling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_restore_error_handling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_update_class_constants (TYPE_2__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static spl_filesystem_object *spl_filesystem_object_create_info(spl_filesystem_object *source, char *file_path, size_t file_path_len, int use_copy, zend_class_entry *ce, zval *return_value) /* {{{ */
{
	spl_filesystem_object *intern;
	zval arg1;
	zend_error_handling error_handling;

	if (!file_path || !file_path_len) {
#if defined(PHP_WIN32)
		zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Cannot create SplFileInfo for empty path");
		if (file_path && !use_copy) {
			efree(file_path);
		}
#else
		if (file_path && !use_copy) {
			efree(file_path);
		}
		file_path_len = 1;
		file_path = "/";
#endif
		return NULL;
	}

	zend_replace_error_handling(EH_THROW, spl_ce_RuntimeException, &error_handling);

	ce = ce ? ce : source->info_class;

	zend_update_class_constants(ce);

	intern = spl_filesystem_from_obj(spl_filesystem_object_new_ex(ce));
	ZVAL_OBJ(return_value, &intern->std);

	if (ce->constructor->common.scope != spl_ce_SplFileInfo) {
		ZVAL_STRINGL(&arg1, file_path, file_path_len);
		zend_call_method_with_1_params(Z_OBJ_P(return_value), ce, &ce->constructor, "__construct", NULL, &arg1);
		zval_ptr_dtor(&arg1);
	} else {
		spl_filesystem_info_set_filename(intern, file_path, file_path_len, use_copy);
	}

	zend_restore_error_handling(&error_handling);
	return intern;
}