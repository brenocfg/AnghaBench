#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
struct TYPE_13__ {char const* function_name; scalar_t__ opcodes; TYPE_2__* scope; } ;
typedef  TYPE_4__ zend_op_array ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ zend_function ;
struct TYPE_15__ {scalar_t__ opline; TYPE_5__* func; } ;
typedef  TYPE_6__ zend_execute_data ;
typedef  int zend_bool ;
struct TYPE_12__ {char const* class; char const* name; } ;
struct TYPE_10__ {char const* name; int /*<<< orphan*/  line; } ;
struct TYPE_16__ {int type; size_t len; char const* str; int /*<<< orphan*/  addr; scalar_t__ num; TYPE_3__ method; TYPE_1__ file; } ;
typedef  TYPE_7__ phpdbg_param_t ;
typedef  int /*<<< orphan*/  phpdbg_opline_ptr_t ;
struct TYPE_11__ {char const* name; } ;

/* Variables and functions */
#define  ADDR_PARAM 133 
#define  FILE_PARAM 132 
#define  METHOD_PARAM 131 
#define  NUMERIC_FUNCTION_PARAM 130 
#define  NUMERIC_METHOD_PARAM 129 
#define  STR_PARAM 128 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  ZEND_USER_FUNCTION ; 
 size_t ZSTR_LEN (char const*) ; 
 char* ZSTR_VAL (char const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char* zend_get_executed_filename () ; 
 int /*<<< orphan*/  zend_get_executed_lineno () ; 

__attribute__((used)) static inline zend_bool phpdbg_find_breakpoint_param(phpdbg_param_t *param, zend_execute_data *execute_data) /* {{{ */
{
	zend_function *function = execute_data->func;

	switch (param->type) {
		case NUMERIC_FUNCTION_PARAM:
		case STR_PARAM: {
			/* function breakpoint */

			if (function->type != ZEND_USER_FUNCTION) {
				return 0;
			}

			{
				const char *str = NULL;
				size_t len = 0L;
				zend_op_array *ops = (zend_op_array*)function;
				str = ops->function_name ? ZSTR_VAL(ops->function_name) : "main";
				len = ops->function_name ? ZSTR_LEN(ops->function_name) : strlen(str);

				if (len == param->len && memcmp(param->str, str, len) == SUCCESS) {
					return param->type == STR_PARAM || execute_data->opline - ops->opcodes == param->num;
				}
			}
		} break;

		case FILE_PARAM: {
			if (param->file.line == zend_get_executed_lineno()) {
				const char *str = zend_get_executed_filename();
				size_t lengths[2] = {strlen(param->file.name), strlen(str)};

				if (lengths[0] == lengths[1]) {
					return (memcmp(
						param->file.name, str, lengths[0]) == SUCCESS);
				}
			}
		} break;

		case NUMERIC_METHOD_PARAM:
		case METHOD_PARAM: {
			if (function->type != ZEND_USER_FUNCTION) {
				return 0;
			}

			{
				zend_op_array *ops = (zend_op_array*) function;

				if (ops->scope) {
					size_t lengths[2] = { strlen(param->method.class), ZSTR_LEN(ops->scope->name) };
					if (lengths[0] == lengths[1] && memcmp(param->method.class, ops->scope->name, lengths[0]) == SUCCESS) {
						lengths[0] = strlen(param->method.name);
						lengths[1] = ZSTR_LEN(ops->function_name);

						if (lengths[0] == lengths[1] && memcmp(param->method.name, ops->function_name, lengths[0]) == SUCCESS) {
							return param->type == METHOD_PARAM || (execute_data->opline - ops->opcodes) == param->num;
						}
					}
				}
			}
		} break;

		case ADDR_PARAM: {
			return ((zend_ulong)(phpdbg_opline_ptr_t)execute_data->opline == param->addr);
		} break;

		default: {
			/* do nothing */
		} break;
	}
	return 0;
}