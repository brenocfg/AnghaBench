#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trace_event_file {int /*<<< orphan*/  tr; } ;
struct hist_trigger_data {int dummy; } ;
struct hist_field {unsigned long flags; int read_once; int operator; int /*<<< orphan*/  fn; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct hist_field** operands; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct hist_field* ERR_PTR (int) ; 
#define  FIELD_OP_MINUS 129 
 int FIELD_OP_NONE ; 
#define  FIELD_OP_PLUS 128 
 int FIELD_OP_UNARY_MINUS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIST_ERR_TOO_MANY_SUBEXPR ; 
 unsigned long HIST_FIELD_FL_EXPR ; 
 unsigned long HIST_FIELD_FL_TIMESTAMP ; 
 unsigned long HIST_FIELD_FL_TIMESTAMP_USECS ; 
 scalar_t__ IS_ERR (struct hist_field*) ; 
 int PTR_ERR (struct hist_field*) ; 
 int check_expr_operands (int /*<<< orphan*/ ,struct hist_field*,struct hist_field*) ; 
 int contains_operator (char*) ; 
 struct hist_field* create_hist_field (struct hist_trigger_data*,int /*<<< orphan*/ *,unsigned long,char*) ; 
 int /*<<< orphan*/  destroy_hist_field (struct hist_field*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errpos (char*) ; 
 int /*<<< orphan*/  expr_str (struct hist_field*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_field_minus ; 
 int /*<<< orphan*/  hist_field_plus ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hist_field* parse_atom (struct hist_trigger_data*,struct trace_event_file*,char*,unsigned long*,char*) ; 
 struct hist_field* parse_unary (struct hist_trigger_data*,struct trace_event_file*,char*,unsigned long,char*,unsigned int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct hist_field *parse_expr(struct hist_trigger_data *hist_data,
				     struct trace_event_file *file,
				     char *str, unsigned long flags,
				     char *var_name, unsigned int level)
{
	struct hist_field *operand1 = NULL, *operand2 = NULL, *expr = NULL;
	unsigned long operand_flags;
	int field_op, ret = -EINVAL;
	char *sep, *operand1_str;

	if (level > 3) {
		hist_err(file->tr, HIST_ERR_TOO_MANY_SUBEXPR, errpos(str));
		return ERR_PTR(-EINVAL);
	}

	field_op = contains_operator(str);

	if (field_op == FIELD_OP_NONE)
		return parse_atom(hist_data, file, str, &flags, var_name);

	if (field_op == FIELD_OP_UNARY_MINUS)
		return parse_unary(hist_data, file, str, flags, var_name, ++level);

	switch (field_op) {
	case FIELD_OP_MINUS:
		sep = "-";
		break;
	case FIELD_OP_PLUS:
		sep = "+";
		break;
	default:
		goto free;
	}

	operand1_str = strsep(&str, sep);
	if (!operand1_str || !str)
		goto free;

	operand_flags = 0;
	operand1 = parse_atom(hist_data, file, operand1_str,
			      &operand_flags, NULL);
	if (IS_ERR(operand1)) {
		ret = PTR_ERR(operand1);
		operand1 = NULL;
		goto free;
	}

	/* rest of string could be another expression e.g. b+c in a+b+c */
	operand_flags = 0;
	operand2 = parse_expr(hist_data, file, str, operand_flags, NULL, ++level);
	if (IS_ERR(operand2)) {
		ret = PTR_ERR(operand2);
		operand2 = NULL;
		goto free;
	}

	ret = check_expr_operands(file->tr, operand1, operand2);
	if (ret)
		goto free;

	flags |= HIST_FIELD_FL_EXPR;

	flags |= operand1->flags &
		(HIST_FIELD_FL_TIMESTAMP | HIST_FIELD_FL_TIMESTAMP_USECS);

	expr = create_hist_field(hist_data, NULL, flags, var_name);
	if (!expr) {
		ret = -ENOMEM;
		goto free;
	}

	operand1->read_once = true;
	operand2->read_once = true;

	expr->operands[0] = operand1;
	expr->operands[1] = operand2;
	expr->operator = field_op;
	expr->name = expr_str(expr, 0);
	expr->type = kstrdup(operand1->type, GFP_KERNEL);
	if (!expr->type) {
		ret = -ENOMEM;
		goto free;
	}

	switch (field_op) {
	case FIELD_OP_MINUS:
		expr->fn = hist_field_minus;
		break;
	case FIELD_OP_PLUS:
		expr->fn = hist_field_plus;
		break;
	default:
		ret = -EINVAL;
		goto free;
	}

	return expr;
 free:
	destroy_hist_field(operand1, 0);
	destroy_hist_field(operand2, 0);
	destroy_hist_field(expr, 0);

	return ERR_PTR(ret);
}