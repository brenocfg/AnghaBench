#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_38__ {TYPE_1__* module; } ;
typedef  TYPE_9__ zend_internal_function ;
struct TYPE_37__ {int fn_flags; TYPE_7__* arg_info; int /*<<< orphan*/ * function_name; TYPE_11__* scope; TYPE_5__* prototype; } ;
struct TYPE_35__ {int fn_flags; int /*<<< orphan*/  line_end; int /*<<< orphan*/  line_start; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * doc_comment; } ;
struct TYPE_27__ {scalar_t__ type; TYPE_8__ common; TYPE_6__ op_array; } ;
typedef  TYPE_10__ zend_function ;
struct TYPE_28__ {int /*<<< orphan*/ * name; TYPE_2__* parent; } ;
typedef  TYPE_11__ zend_class_entry ;
struct TYPE_29__ {int /*<<< orphan*/ * s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_12__ smart_str ;
struct TYPE_36__ {int /*<<< orphan*/  type; } ;
struct TYPE_33__ {TYPE_3__* scope; } ;
struct TYPE_34__ {TYPE_4__ common; } ;
struct TYPE_32__ {int /*<<< orphan*/ * name; } ;
struct TYPE_31__ {int /*<<< orphan*/  function_table; } ;
struct TYPE_30__ {char* name; } ;

/* Variables and functions */
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_CLOSURE ; 
 int ZEND_ACC_CTOR ; 
 int ZEND_ACC_DEPRECATED ; 
 int ZEND_ACC_DTOR ; 
 int ZEND_ACC_FINAL ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_PPP_MASK ; 
#define  ZEND_ACC_PRIVATE 130 
#define  ZEND_ACC_PROTECTED 129 
#define  ZEND_ACC_PUBLIC 128 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int ZEND_ACC_STATIC ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 scalar_t__ ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _function_closure_string (TYPE_12__*,TYPE_10__*,char*) ; 
 int /*<<< orphan*/  _function_parameter_string (TYPE_12__*,TYPE_10__*,char*) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_12__*) ; 
 int /*<<< orphan*/  smart_str_append_printf (TYPE_12__*,char*,...) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_12__*,char) ; 
 int /*<<< orphan*/  smart_str_appendl (TYPE_12__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_12__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_10__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _function_string(smart_str *str, zend_function *fptr, zend_class_entry *scope, char* indent)
{
	smart_str param_indent = {0};
	zend_function *overwrites;
	zend_string *lc_name;

	/* TBD: Repair indenting of doc comment (or is this to be done in the parser?)
	 * What's "wrong" is that any whitespace before the doc comment start is
	 * swallowed, leading to an unaligned comment.
	 */
	if (fptr->type == ZEND_USER_FUNCTION && fptr->op_array.doc_comment) {
		smart_str_append_printf(str, "%s%s\n", indent, ZSTR_VAL(fptr->op_array.doc_comment));
	}

	smart_str_appendl(str, indent, strlen(indent));
	smart_str_append_printf(str, fptr->common.fn_flags & ZEND_ACC_CLOSURE ? "Closure [ " : (fptr->common.scope ? "Method [ " : "Function [ "));
	smart_str_append_printf(str, (fptr->type == ZEND_USER_FUNCTION) ? "<user" : "<internal");
	if (fptr->common.fn_flags & ZEND_ACC_DEPRECATED) {
		smart_str_appends(str, ", deprecated");
	}
	if (fptr->type == ZEND_INTERNAL_FUNCTION && ((zend_internal_function*)fptr)->module) {
		smart_str_append_printf(str, ":%s", ((zend_internal_function*)fptr)->module->name);
	}

	if (scope && fptr->common.scope) {
		if (fptr->common.scope != scope) {
			smart_str_append_printf(str, ", inherits %s", ZSTR_VAL(fptr->common.scope->name));
		} else if (fptr->common.scope->parent) {
			lc_name = zend_string_tolower(fptr->common.function_name);
			if ((overwrites = zend_hash_find_ptr(&fptr->common.scope->parent->function_table, lc_name)) != NULL) {
				if (fptr->common.scope != overwrites->common.scope) {
					smart_str_append_printf(str, ", overwrites %s", ZSTR_VAL(overwrites->common.scope->name));
				}
			}
			zend_string_release_ex(lc_name, 0);
		}
	}
	if (fptr->common.prototype && fptr->common.prototype->common.scope) {
		smart_str_append_printf(str, ", prototype %s", ZSTR_VAL(fptr->common.prototype->common.scope->name));
	}
	if (fptr->common.fn_flags & ZEND_ACC_CTOR) {
		smart_str_appends(str, ", ctor");
	}
	if (fptr->common.fn_flags & ZEND_ACC_DTOR) {
		smart_str_appends(str, ", dtor");
	}
	smart_str_appends(str, "> ");

	if (fptr->common.fn_flags & ZEND_ACC_ABSTRACT) {
		smart_str_appends(str, "abstract ");
	}
	if (fptr->common.fn_flags & ZEND_ACC_FINAL) {
		smart_str_appends(str, "final ");
	}
	if (fptr->common.fn_flags & ZEND_ACC_STATIC) {
		smart_str_appends(str, "static ");
	}

	if (fptr->common.scope) {
		/* These are mutually exclusive */
		switch (fptr->common.fn_flags & ZEND_ACC_PPP_MASK) {
			case ZEND_ACC_PUBLIC:
				smart_str_appends(str, "public ");
				break;
			case ZEND_ACC_PRIVATE:
				smart_str_appends(str, "private ");
				break;
			case ZEND_ACC_PROTECTED:
				smart_str_appends(str, "protected ");
				break;
			default:
				smart_str_appends(str, "<visibility error> ");
				break;
		}
		smart_str_appends(str, "method ");
	} else {
		smart_str_appends(str, "function ");
	}

	if (fptr->op_array.fn_flags & ZEND_ACC_RETURN_REFERENCE) {
		smart_str_appendc(str, '&');
	}
	smart_str_append_printf(str, "%s ] {\n", ZSTR_VAL(fptr->common.function_name));
	/* The information where a function is declared is only available for user classes */
	if (fptr->type == ZEND_USER_FUNCTION) {
		smart_str_append_printf(str, "%s  @@ %s %d - %d\n", indent,
						ZSTR_VAL(fptr->op_array.filename),
						fptr->op_array.line_start,
						fptr->op_array.line_end);
	}
	smart_str_append_printf(&param_indent, "%s  ", indent);
	smart_str_0(&param_indent);
	if (fptr->common.fn_flags & ZEND_ACC_CLOSURE) {
		_function_closure_string(str, fptr, ZSTR_VAL(param_indent.s));
	}
	_function_parameter_string(str, fptr, ZSTR_VAL(param_indent.s));
	smart_str_free(&param_indent);
	if (fptr->op_array.fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
		smart_str_append_printf(str, "  %s- Return [ ", indent);
		if (ZEND_TYPE_IS_SET(fptr->common.arg_info[-1].type)) {
			zend_string *type_str = zend_type_to_string(fptr->common.arg_info[-1].type);
			smart_str_append_printf(str, "%s ", ZSTR_VAL(type_str));
			zend_string_release(type_str);
		}
		smart_str_appends(str, "]\n");
	}
	smart_str_append_printf(str, "%s}\n", indent);
}