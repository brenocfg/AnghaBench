#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int type; struct tep_filter_arg* right; struct tep_filter_arg* left; } ;
struct TYPE_15__ {int type; TYPE_6__* field; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct TYPE_13__ {TYPE_6__* field; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int type; char* str; } ;
struct TYPE_10__ {struct tep_filter_arg* right; } ;
struct TYPE_9__ {struct tep_filter_arg* right; } ;
struct tep_filter_arg {int type; TYPE_8__ num; TYPE_7__ str; TYPE_5__ field; TYPE_4__ boolean; TYPE_3__ value; TYPE_2__ op; TYPE_1__ exp; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;
struct TYPE_14__ {size_t size; } ;

/* Variables and functions */
 int REG_ICASE ; 
 int REG_NOSUB ; 
 int TEP_ERRNO__ILLEGAL_INTEGER_CMP ; 
 int TEP_ERRNO__ILLEGAL_LVALUE ; 
 int TEP_ERRNO__ILLEGAL_RVALUE ; 
 int TEP_ERRNO__ILLEGAL_STRING_CMP ; 
 int TEP_ERRNO__INVALID_REGEX ; 
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 int TEP_ERRNO__SYNTAX_ERROR ; 
 int TEP_FILTER_ARG_BOOLEAN ; 
#define  TEP_FILTER_ARG_EXP 139 
#define  TEP_FILTER_ARG_FIELD 138 
#define  TEP_FILTER_ARG_NUM 137 
#define  TEP_FILTER_ARG_OP 136 
 int const TEP_FILTER_ARG_STR ; 
#define  TEP_FILTER_ARG_VALUE 135 
#define  TEP_FILTER_CHAR 134 
#define  TEP_FILTER_CMP_EQ 133 
 int TEP_FILTER_CMP_MATCH ; 
#define  TEP_FILTER_CMP_NE 132 
 int TEP_FILTER_CMP_NOT_MATCH ; 
#define  TEP_FILTER_CMP_NOT_REGEX 131 
#define  TEP_FILTER_CMP_REGEX 130 
 int /*<<< orphan*/  TEP_FILTER_FALSE ; 
#define  TEP_FILTER_NUMBER 129 
#define  TEP_FILTER_STRING 128 
 int /*<<< orphan*/  free_arg (struct tep_filter_arg*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tep_filter_arg*,int /*<<< orphan*/ ,int) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  show_error (char*,char*,...) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static enum tep_errno
add_right(struct tep_filter_arg *op, struct tep_filter_arg *arg, char *error_str)
{
	struct tep_filter_arg *left;
	char *str;
	int op_type;
	int ret;

	switch (op->type) {
	case TEP_FILTER_ARG_EXP:
		if (op->exp.right)
			goto out_fail;
		op->exp.right = arg;
		break;

	case TEP_FILTER_ARG_OP:
		if (op->op.right)
			goto out_fail;
		op->op.right = arg;
		break;

	case TEP_FILTER_ARG_NUM:
		if (op->op.right)
			goto out_fail;
		/*
		 * The arg must be num, str, or field
		 */
		switch (arg->type) {
		case TEP_FILTER_ARG_VALUE:
		case TEP_FILTER_ARG_FIELD:
			break;
		default:
			show_error(error_str, "Illegal rvalue");
			return TEP_ERRNO__ILLEGAL_RVALUE;
		}

		/*
		 * Depending on the type, we may need to
		 * convert this to a string or regex.
		 */
		switch (arg->value.type) {
		case TEP_FILTER_CHAR:
			/*
			 * A char should be converted to number if
			 * the string is 1 byte, and the compare
			 * is not a REGEX.
			 */
			if (strlen(arg->value.str) == 1 &&
			    op->num.type != TEP_FILTER_CMP_REGEX &&
			    op->num.type != TEP_FILTER_CMP_NOT_REGEX) {
				arg->value.type = TEP_FILTER_NUMBER;
				goto do_int;
			}
			/* fall through */
		case TEP_FILTER_STRING:

			/* convert op to a string arg */
			op_type = op->num.type;
			left = op->num.left;
			str = arg->value.str;

			/* reset the op for the new field */
			memset(op, 0, sizeof(*op));

			/*
			 * If left arg was a field not found then
			 * NULL the entire op.
			 */
			if (left->type == TEP_FILTER_ARG_BOOLEAN) {
				free_arg(left);
				free_arg(arg);
				op->type = TEP_FILTER_ARG_BOOLEAN;
				op->boolean.value = TEP_FILTER_FALSE;
				break;
			}

			/* Left arg must be a field */
			if (left->type != TEP_FILTER_ARG_FIELD) {
				show_error(error_str,
					   "Illegal lvalue for string comparison");
				return TEP_ERRNO__ILLEGAL_LVALUE;
			}

			/* Make sure this is a valid string compare */
			switch (op_type) {
			case TEP_FILTER_CMP_EQ:
				op_type = TEP_FILTER_CMP_MATCH;
				break;
			case TEP_FILTER_CMP_NE:
				op_type = TEP_FILTER_CMP_NOT_MATCH;
				break;

			case TEP_FILTER_CMP_REGEX:
			case TEP_FILTER_CMP_NOT_REGEX:
				ret = regcomp(&op->str.reg, str, REG_ICASE|REG_NOSUB);
				if (ret) {
					show_error(error_str,
						   "RegEx '%s' did not compute",
						   str);
					return TEP_ERRNO__INVALID_REGEX;
				}
				break;
			default:
				show_error(error_str,
					   "Illegal comparison for string");
				return TEP_ERRNO__ILLEGAL_STRING_CMP;
			}

			op->type = TEP_FILTER_ARG_STR;
			op->str.type = op_type;
			op->str.field = left->field.field;
			op->str.val = strdup(str);
			if (!op->str.val) {
				show_error(error_str, "Failed to allocate string filter");
				return TEP_ERRNO__MEM_ALLOC_FAILED;
			}
			/*
			 * Need a buffer to copy data for tests
			 */
			op->str.buffer = malloc(op->str.field->size + 1);
			if (!op->str.buffer) {
				show_error(error_str, "Failed to allocate string filter");
				return TEP_ERRNO__MEM_ALLOC_FAILED;
			}
			/* Null terminate this buffer */
			op->str.buffer[op->str.field->size] = 0;

			/* We no longer have left or right args */
			free_arg(arg);
			free_arg(left);

			break;

		case TEP_FILTER_NUMBER:

 do_int:
			switch (op->num.type) {
			case TEP_FILTER_CMP_REGEX:
			case TEP_FILTER_CMP_NOT_REGEX:
				show_error(error_str,
					   "Op not allowed with integers");
				return TEP_ERRNO__ILLEGAL_INTEGER_CMP;

			default:
				break;
			}

			/* numeric compare */
			op->num.right = arg;
			break;
		default:
			goto out_fail;
		}
		break;
	default:
		goto out_fail;
	}

	return 0;

 out_fail:
	show_error(error_str, "Syntax error");
	return TEP_ERRNO__SYNTAX_ERROR;
}