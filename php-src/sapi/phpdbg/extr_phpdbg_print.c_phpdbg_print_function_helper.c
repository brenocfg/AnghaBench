#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  last; int /*<<< orphan*/  filename; int /*<<< orphan*/  line_end; int /*<<< orphan*/  line_start; TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_12__ {int /*<<< orphan*/  lineno; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_10__ {int /*<<< orphan*/  function_name; TYPE_1__* scope; } ;
struct TYPE_13__ {int type; TYPE_2__ common; TYPE_3__ op_array; } ;
typedef  TYPE_5__ zend_function ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  ZEND_USER_FUNCTION 128 
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* phpdbg_decode_opline (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  phpdbg_writeln (char*,char*,char*,char*,...) ; 

__attribute__((used)) static inline void phpdbg_print_function_helper(zend_function *method) /* {{{ */
{
	switch (method->type) {
		case ZEND_USER_FUNCTION: {
			zend_op_array* op_array = &(method->op_array);

			if (op_array) {
				zend_op *opline = &(op_array->opcodes[0]);
				uint32_t opcode = 0,
				end = op_array->last-1;

				if (method->common.scope) {
					phpdbg_writeln("printoplineinfo", "type=\"User\" startline=\"%d\" endline=\"%d\" method=\"%s::%s\" file=\"%s\" opline=\"%p\"", "L%d-%d %s::%s() %s - %p + %d ops",
						op_array->line_start,
						op_array->line_end,
						ZSTR_VAL(method->common.scope->name),
						ZSTR_VAL(method->common.function_name),
						op_array->filename ? ZSTR_VAL(op_array->filename) : "unknown",
						opline,
						op_array->last);
				} else {
					phpdbg_writeln("printoplineinfo", "type=\"User\" startline=\"%d\" endline=\"%d\" function=\"%s\" file=\"%s\" opline=\"%p\"", "L%d-%d %s() %s - %p + %d ops",
						op_array->line_start,
						op_array->line_end,
						method->common.function_name ? ZSTR_VAL(method->common.function_name) : "{main}",
						op_array->filename ? ZSTR_VAL(op_array->filename) : "unknown",
						opline,
						op_array->last);
				}

				do {
					char *decode = phpdbg_decode_opline(op_array, opline);
					phpdbg_writeln("print", "line=\"%u\" opnum=\"%u\" op=\"%s\"", " L%-4u #%-5u %s",
						opline->lineno,
						opcode,
						decode);
					efree(decode);
					opline++;
				} while (opcode++ < end);
			}
		} break;

		default: {
			if (method->common.scope) {
				phpdbg_writeln("printoplineinfo", "type=\"Internal\" method=\"%s::%s\"", "\tInternal %s::%s()", ZSTR_VAL(method->common.scope->name), ZSTR_VAL(method->common.function_name));
			} else {
				phpdbg_writeln("printoplineinfo", "type=\"Internal\" function=\"%s\"", "\tInternal %s()", ZSTR_VAL(method->common.function_name));
			}
		}
	}
}