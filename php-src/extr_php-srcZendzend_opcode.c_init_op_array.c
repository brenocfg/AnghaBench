#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_4__ {int* refcount; int cache_size; int /*<<< orphan*/  reserved; int /*<<< orphan*/  run_time_cache; int /*<<< orphan*/ * literals; scalar_t__ last_literal; scalar_t__ fn_flags; scalar_t__ last_try_catch; int /*<<< orphan*/ * static_variables; int /*<<< orphan*/  static_variables_ptr; scalar_t__ last_live_range; int /*<<< orphan*/ * try_catch_array; int /*<<< orphan*/ * live_range; int /*<<< orphan*/ * prototype; int /*<<< orphan*/ * scope; scalar_t__ required_num_args; scalar_t__ num_args; int /*<<< orphan*/ * arg_info; int /*<<< orphan*/ * doc_comment; int /*<<< orphan*/  filename; int /*<<< orphan*/ * function_name; scalar_t__ T; int /*<<< orphan*/ * vars; scalar_t__ last_var; scalar_t__ opcodes; scalar_t__ last; scalar_t__* arg_flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_op ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  llist_apply_with_arg_func_t ;

/* Variables and functions */
 int ZEND_EXTENSIONS_HAVE_OP_ARRAY_CTOR ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int ZEND_MAX_RESERVED_RESOURCES ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zend_extension_flags ; 
 scalar_t__ zend_extension_op_array_ctor_handler ; 
 int /*<<< orphan*/  zend_extensions ; 
 int /*<<< orphan*/  zend_get_compiled_filename () ; 
 int /*<<< orphan*/  zend_llist_apply_with_argument (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int zend_op_array_extension_handles ; 

void init_op_array(zend_op_array *op_array, zend_uchar type, int initial_ops_size)
{
	op_array->type = type;
	op_array->arg_flags[0] = 0;
	op_array->arg_flags[1] = 0;
	op_array->arg_flags[2] = 0;

	op_array->refcount = (uint32_t *) emalloc(sizeof(uint32_t));
	*op_array->refcount = 1;
	op_array->last = 0;
	op_array->opcodes = emalloc(initial_ops_size * sizeof(zend_op));

	op_array->last_var = 0;
	op_array->vars = NULL;

	op_array->T = 0;

	op_array->function_name = NULL;
	op_array->filename = zend_get_compiled_filename();
	op_array->doc_comment = NULL;

	op_array->arg_info = NULL;
	op_array->num_args = 0;
	op_array->required_num_args = 0;

	op_array->scope = NULL;
	op_array->prototype = NULL;

	op_array->live_range = NULL;
	op_array->try_catch_array = NULL;
	op_array->last_live_range = 0;

	op_array->static_variables = NULL;
	ZEND_MAP_PTR_INIT(op_array->static_variables_ptr, &op_array->static_variables);
	op_array->last_try_catch = 0;

	op_array->fn_flags = 0;

	op_array->last_literal = 0;
	op_array->literals = NULL;

	ZEND_MAP_PTR_INIT(op_array->run_time_cache, NULL);
	op_array->cache_size = zend_op_array_extension_handles * sizeof(void*);

	memset(op_array->reserved, 0, ZEND_MAX_RESERVED_RESOURCES * sizeof(void*));

	if (zend_extension_flags & ZEND_EXTENSIONS_HAVE_OP_ARRAY_CTOR) {
		zend_llist_apply_with_argument(&zend_extensions, (llist_apply_with_arg_func_t) zend_extension_op_array_ctor_handler, op_array);
	}
}