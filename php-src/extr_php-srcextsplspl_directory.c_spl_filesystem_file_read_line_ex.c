#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_execute_data ;
struct TYPE_11__ {int /*<<< orphan*/  current_zval; int /*<<< orphan*/  current_line_len; scalar_t__ current_line; int /*<<< orphan*/  current_line_num; TYPE_5__* func_getCurr; int /*<<< orphan*/  escape; int /*<<< orphan*/  enclosure; int /*<<< orphan*/  delimiter; int /*<<< orphan*/  stream; } ;
struct TYPE_12__ {TYPE_2__ file; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_4__ spl_filesystem_object ;
struct TYPE_10__ {scalar_t__ scope; } ;
struct TYPE_14__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EG (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  SPL_FILE_OBJECT_READ_CSV ; 
 scalar_t__ SPL_HAS_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_THIS ; 
 int /*<<< orphan*/  ZVAL_COPY_DEREF (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_execute_data ; 
 scalar_t__ estrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_ce_RuntimeException ; 
 scalar_t__ spl_ce_SplFileObject ; 
 int /*<<< orphan*/  spl_filesystem_file_free_line (TYPE_4__*) ; 
 int spl_filesystem_file_read (TYPE_4__*,int) ; 
 int spl_filesystem_file_read_csv (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_filesystem_file_read_line_ex(zval * this_ptr, spl_filesystem_object *intern, int silent) /* {{{ */
{
	zval retval;

	/* 1) use fgetcsv? 2) overloaded call the function, 3) do it directly */
	if (SPL_HAS_FLAG(intern->flags, SPL_FILE_OBJECT_READ_CSV) || intern->u.file.func_getCurr->common.scope != spl_ce_SplFileObject) {
		if (php_stream_eof(intern->u.file.stream)) {
			if (!silent) {
				zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Cannot read from file %s", intern->file_name);
			}
			return FAILURE;
		}
		if (SPL_HAS_FLAG(intern->flags, SPL_FILE_OBJECT_READ_CSV)) {
			return spl_filesystem_file_read_csv(intern, intern->u.file.delimiter, intern->u.file.enclosure, intern->u.file.escape, NULL);
		} else {
			zend_execute_data *execute_data = EG(current_execute_data);
			zend_call_method_with_0_params(Z_OBJ_P(this_ptr), Z_OBJCE_P(ZEND_THIS), &intern->u.file.func_getCurr, "getCurrentLine", &retval);
		}
		if (!Z_ISUNDEF(retval)) {
			if (intern->u.file.current_line || !Z_ISUNDEF(intern->u.file.current_zval)) {
				intern->u.file.current_line_num++;
			}
			spl_filesystem_file_free_line(intern);
			if (Z_TYPE(retval) == IS_STRING) {
				intern->u.file.current_line = estrndup(Z_STRVAL(retval), Z_STRLEN(retval));
				intern->u.file.current_line_len = Z_STRLEN(retval);
			} else {
				zval *value = &retval;

				ZVAL_COPY_DEREF(&intern->u.file.current_zval, value);
			}
			zval_ptr_dtor(&retval);
			return SUCCESS;
		} else {
			return FAILURE;
		}
	} else {
		return spl_filesystem_file_read(intern, silent);
	}
}