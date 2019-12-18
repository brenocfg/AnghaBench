#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_9__ {scalar_t__ opcode; scalar_t__ op2_type; int /*<<< orphan*/  op2; } ;
typedef  TYPE_2__ zend_op ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ zend_internal_arg_info ;
struct TYPE_8__ {int fn_flags; int /*<<< orphan*/  scope; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_1__ common; } ;
typedef  TYPE_4__ zend_function ;
typedef  int /*<<< orphan*/  zend_bool ;
typedef  int /*<<< orphan*/  uint32_t ;
struct _zend_arg_info {int /*<<< orphan*/ * name; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_FALSE ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ IS_TRUE ; 
 scalar_t__ IS_UNUSED ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  RT_CONSTANT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_USER_ARG_INFO ; 
 scalar_t__ ZEND_ARG_IS_VARIADIC (struct _zend_arg_info*) ; 
 scalar_t__ ZEND_ARG_SEND_MODE (struct _zend_arg_info*) ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 scalar_t__ ZEND_RECV_INIT ; 
 scalar_t__ ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* _get_recv_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appends (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 scalar_t__ zval_update_constant_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _parameter_string(smart_str *str, zend_function *fptr, struct _zend_arg_info *arg_info, uint32_t offset, zend_bool required, char* indent)
{
	smart_str_append_printf(str, "Parameter #%d [ ", offset);
	if (!required) {
		smart_str_append_printf(str, "<optional> ");
	} else {
		smart_str_append_printf(str, "<required> ");
	}
	if (ZEND_TYPE_IS_SET(arg_info->type)) {
		zend_string *type_str = zend_type_to_string(arg_info->type);
		smart_str_append_printf(str, "%s ", ZSTR_VAL(type_str));
		zend_string_release(type_str);
	}
	if (ZEND_ARG_SEND_MODE(arg_info)) {
		smart_str_appendc(str, '&');
	}
	if (ZEND_ARG_IS_VARIADIC(arg_info)) {
		smart_str_appends(str, "...");
	}
	if (arg_info->name) {
		smart_str_append_printf(str, "$%s",
			(fptr->type == ZEND_INTERNAL_FUNCTION &&
			 !(fptr->common.fn_flags & ZEND_ACC_USER_ARG_INFO)) ?
			((zend_internal_arg_info*)arg_info)->name :
			ZSTR_VAL(arg_info->name));
	} else {
		smart_str_append_printf(str, "$param%d", offset);
	}
	if (fptr->type == ZEND_USER_FUNCTION && !required) {
		zend_op *precv = _get_recv_op((zend_op_array*)fptr, offset);
		if (precv && precv->opcode == ZEND_RECV_INIT && precv->op2_type != IS_UNUSED) {
			zval zv;

			smart_str_appends(str, " = ");
			ZVAL_COPY(&zv, RT_CONSTANT(precv, precv->op2));
			if (UNEXPECTED(zval_update_constant_ex(&zv, fptr->common.scope) == FAILURE)) {
				zval_ptr_dtor(&zv);
				return;
			}
			if (Z_TYPE(zv) == IS_TRUE) {
				smart_str_appends(str, "true");
			} else if (Z_TYPE(zv) == IS_FALSE) {
				smart_str_appends(str, "false");
			} else if (Z_TYPE(zv) == IS_NULL) {
				smart_str_appends(str, "NULL");
			} else if (Z_TYPE(zv) == IS_STRING) {
				smart_str_appendc(str, '\'');
				smart_str_appendl(str, Z_STRVAL(zv), MIN(Z_STRLEN(zv), 15));
				if (Z_STRLEN(zv) > 15) {
					smart_str_appends(str, "...");
				}
				smart_str_appendc(str, '\'');
			} else if (Z_TYPE(zv) == IS_ARRAY) {
				smart_str_appends(str, "Array");
			} else {
				zend_string *tmp_zv_str;
				zend_string *zv_str = zval_get_tmp_string(&zv, &tmp_zv_str);
				smart_str_append(str, zv_str);
				zend_tmp_string_release(tmp_zv_str);
			}
			zval_ptr_dtor(&zv);
		}
	}
	smart_str_appends(str, " ]");
}