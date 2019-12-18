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
typedef  enum field_op_id { ____Placeholder_field_op_id } field_op_id ;

/* Variables and functions */
 int FIELD_OP_MINUS ; 
 int FIELD_OP_NONE ; 
 int FIELD_OP_PLUS ; 
 int FIELD_OP_UNARY_MINUS ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int contains_operator(char *str)
{
	enum field_op_id field_op = FIELD_OP_NONE;
	char *op;

	op = strpbrk(str, "+-");
	if (!op)
		return FIELD_OP_NONE;

	switch (*op) {
	case '-':
		if (*str == '-')
			field_op = FIELD_OP_UNARY_MINUS;
		else
			field_op = FIELD_OP_MINUS;
		break;
	case '+':
		field_op = FIELD_OP_PLUS;
		break;
	default:
		break;
	}

	return field_op;
}