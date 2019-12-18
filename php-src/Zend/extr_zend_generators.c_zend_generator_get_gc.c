#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_14__ {scalar_t__ last_var; scalar_t__ T; int num_args; scalar_t__ opcodes; scalar_t__ last_live_range; TYPE_3__* live_range; } ;
typedef  TYPE_2__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_15__ {scalar_t__ start; scalar_t__ end; scalar_t__ var; } ;
typedef  TYPE_3__ zend_live_range ;
struct TYPE_13__ {TYPE_4__* root; } ;
struct TYPE_18__ {scalar_t__ children; TYPE_1__ ptr; } ;
struct TYPE_16__ {scalar_t__ gc_buffer_size; TYPE_7__ node; int /*<<< orphan*/  std; int /*<<< orphan*/  values; int /*<<< orphan*/  retval; int /*<<< orphan*/  key; int /*<<< orphan*/  value; int /*<<< orphan*/ * gc_buffer; TYPE_5__* execute_data; } ;
typedef  TYPE_4__ zend_generator ;
struct TYPE_17__ {scalar_t__ opline; int /*<<< orphan*/ * symbol_table; int /*<<< orphan*/  This; } ;
typedef  TYPE_5__ zend_execute_data ;
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {TYPE_2__ op_array; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_10__* EX (int /*<<< orphan*/ ) ; 
 int EX_CALL_INFO () ; 
 int EX_NUM_ARGS () ; 
 int /*<<< orphan*/ * EX_VAR (scalar_t__) ; 
 int /*<<< orphan*/ * EX_VAR_NUM (scalar_t__) ; 
 int ZEND_CALL_CLOSURE ; 
 int ZEND_CALL_FREE_EXTRA_ARGS ; 
 int ZEND_CALL_HAS_SYMBOL_TABLE ; 
 int ZEND_CALL_RELEASE_THIS ; 
 int /*<<< orphan*/ * ZEND_CLOSURE_OBJECT (TYPE_10__*) ; 
 scalar_t__ ZEND_LIVE_LOOP ; 
 scalar_t__ ZEND_LIVE_MASK ; 
 scalar_t__ ZEND_LIVE_TMPVAR ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_OBJ (int /*<<< orphan*/ ) ; 
 scalar_t__ calc_gc_buffer_size (TYPE_4__*) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/ * safe_erealloc (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* zend_generator_get_child (TYPE_7__*,TYPE_4__*) ; 

__attribute__((used)) static HashTable *zend_generator_get_gc(zend_object *object, zval **table, int *n) /* {{{ */
{
	zend_generator *generator = (zend_generator*)object;
	zend_execute_data *execute_data = generator->execute_data;
	zend_op_array *op_array;
	zval *gc_buffer;
	uint32_t gc_buffer_size;

	if (!execute_data) {
		/* If the generator has been closed, it can only hold on to three values: The value, key
		 * and retval. These three zvals are stored sequentially starting at &generator->value. */
		*table = &generator->value;
		*n = 3;
		return NULL;
	}

	op_array = &EX(func)->op_array;
	gc_buffer_size = calc_gc_buffer_size(generator);
	if (generator->gc_buffer_size < gc_buffer_size) {
		generator->gc_buffer = safe_erealloc(generator->gc_buffer, sizeof(zval), gc_buffer_size, 0);
		generator->gc_buffer_size = gc_buffer_size;
	}

	*n = gc_buffer_size;
	*table = gc_buffer = generator->gc_buffer;

	ZVAL_COPY_VALUE(gc_buffer++, &generator->value);
	ZVAL_COPY_VALUE(gc_buffer++, &generator->key);
	ZVAL_COPY_VALUE(gc_buffer++, &generator->retval);
	ZVAL_COPY_VALUE(gc_buffer++, &generator->values);

	if (!(EX_CALL_INFO() & ZEND_CALL_HAS_SYMBOL_TABLE)) {
		uint32_t i, num_cvs = EX(func)->op_array.last_var;
		for (i = 0; i < num_cvs; i++) {
			ZVAL_COPY_VALUE(gc_buffer++, EX_VAR_NUM(i));
		}
	}

	if (EX_CALL_INFO() & ZEND_CALL_FREE_EXTRA_ARGS) {
		zval *zv = EX_VAR_NUM(op_array->last_var + op_array->T);
		zval *end = zv + (EX_NUM_ARGS() - op_array->num_args);
		while (zv != end) {
			ZVAL_COPY_VALUE(gc_buffer++, zv++);
		}
	}

	if (EX_CALL_INFO() & ZEND_CALL_RELEASE_THIS) {
		ZVAL_OBJ(gc_buffer++, Z_OBJ(execute_data->This));
	}
	if (EX_CALL_INFO() & ZEND_CALL_CLOSURE) {
		ZVAL_OBJ(gc_buffer++, ZEND_CLOSURE_OBJECT(EX(func)));
	}

	if (execute_data->opline != op_array->opcodes) {
		uint32_t i, op_num = execute_data->opline - op_array->opcodes - 1;
		for (i = 0; i < op_array->last_live_range; i++) {
			const zend_live_range *range = &op_array->live_range[i];
			if (range->start > op_num) {
				break;
			} else if (op_num < range->end) {
				uint32_t kind = range->var & ZEND_LIVE_MASK;
				uint32_t var_num = range->var & ~ZEND_LIVE_MASK;
				zval *var = EX_VAR(var_num);
				if (kind == ZEND_LIVE_TMPVAR || kind == ZEND_LIVE_LOOP) {
					ZVAL_COPY_VALUE(gc_buffer++, var);
				}
			}
		}
	}

	if (generator->node.children == 0) {
		zend_generator *root = generator->node.ptr.root;
		while (root != generator) {
			ZVAL_OBJ(gc_buffer++, &root->std);
			root = zend_generator_get_child(&root->node, generator);
		}
	}

	if (EX_CALL_INFO() & ZEND_CALL_HAS_SYMBOL_TABLE) {
		return execute_data->symbol_table;
	} else {
		return NULL;
	}
}