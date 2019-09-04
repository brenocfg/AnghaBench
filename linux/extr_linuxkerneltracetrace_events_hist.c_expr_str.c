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
struct hist_field {int operator; struct hist_field** operands; } ;

/* Variables and functions */
#define  FIELD_OP_MINUS 129 
#define  FIELD_OP_PLUS 128 
 int FIELD_OP_UNARY_MINUS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_FILTER_STR_VAL ; 
 int /*<<< orphan*/  expr_field_str (struct hist_field*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static char *expr_str(struct hist_field *field, unsigned int level)
{
	char *expr;

	if (level > 1)
		return NULL;

	expr = kzalloc(MAX_FILTER_STR_VAL, GFP_KERNEL);
	if (!expr)
		return NULL;

	if (!field->operands[0]) {
		expr_field_str(field, expr);
		return expr;
	}

	if (field->operator == FIELD_OP_UNARY_MINUS) {
		char *subexpr;

		strcat(expr, "-(");
		subexpr = expr_str(field->operands[0], ++level);
		if (!subexpr) {
			kfree(expr);
			return NULL;
		}
		strcat(expr, subexpr);
		strcat(expr, ")");

		kfree(subexpr);

		return expr;
	}

	expr_field_str(field->operands[0], expr);

	switch (field->operator) {
	case FIELD_OP_MINUS:
		strcat(expr, "-");
		break;
	case FIELD_OP_PLUS:
		strcat(expr, "+");
		break;
	default:
		kfree(expr);
		return NULL;
	}

	expr_field_str(field->operands[1], expr);

	return expr;
}