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
typedef  enum tep_filter_op_type { ____Placeholder_tep_filter_op_type } tep_filter_op_type ;
typedef  enum tep_filter_exp_type { ____Placeholder_tep_filter_exp_type } tep_filter_exp_type ;
typedef  enum tep_filter_cmp_type { ____Placeholder_tep_filter_cmp_type } tep_filter_cmp_type ;
typedef  enum op_type { ____Placeholder_op_type } op_type ;

/* Variables and functions */
 int OP_BOOL ; 
 int OP_CMP ; 
 int OP_EXP ; 
 int OP_NONE ; 
 int OP_NOT ; 
 int TEP_FILTER_CMP_EQ ; 
 int TEP_FILTER_CMP_GE ; 
 int TEP_FILTER_CMP_GT ; 
 int TEP_FILTER_CMP_LE ; 
 int TEP_FILTER_CMP_LT ; 
 int TEP_FILTER_CMP_NE ; 
 int TEP_FILTER_CMP_NONE ; 
 int TEP_FILTER_CMP_NOT_REGEX ; 
 int TEP_FILTER_CMP_REGEX ; 
 int TEP_FILTER_EXP_ADD ; 
 int TEP_FILTER_EXP_AND ; 
 int TEP_FILTER_EXP_DIV ; 
 int TEP_FILTER_EXP_LSHIFT ; 
 int TEP_FILTER_EXP_MOD ; 
 int TEP_FILTER_EXP_MUL ; 
 int TEP_FILTER_EXP_NONE ; 
 int TEP_FILTER_EXP_NOT ; 
 int TEP_FILTER_EXP_OR ; 
 int TEP_FILTER_EXP_RSHIFT ; 
 int TEP_FILTER_EXP_SUB ; 
 int TEP_FILTER_EXP_XOR ; 
 int TEP_FILTER_OP_AND ; 
 int TEP_FILTER_OP_NOT ; 
 int TEP_FILTER_OP_OR ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static enum op_type process_op(const char *token,
			       enum tep_filter_op_type *btype,
			       enum tep_filter_cmp_type *ctype,
			       enum tep_filter_exp_type *etype)
{
	*btype = TEP_FILTER_OP_NOT;
	*etype = TEP_FILTER_EXP_NONE;
	*ctype = TEP_FILTER_CMP_NONE;

	if (strcmp(token, "&&") == 0)
		*btype = TEP_FILTER_OP_AND;
	else if (strcmp(token, "||") == 0)
		*btype = TEP_FILTER_OP_OR;
	else if (strcmp(token, "!") == 0)
		return OP_NOT;

	if (*btype != TEP_FILTER_OP_NOT)
		return OP_BOOL;

	/* Check for value expressions */
	if (strcmp(token, "+") == 0) {
		*etype = TEP_FILTER_EXP_ADD;
	} else if (strcmp(token, "-") == 0) {
		*etype = TEP_FILTER_EXP_SUB;
	} else if (strcmp(token, "*") == 0) {
		*etype = TEP_FILTER_EXP_MUL;
	} else if (strcmp(token, "/") == 0) {
		*etype = TEP_FILTER_EXP_DIV;
	} else if (strcmp(token, "%") == 0) {
		*etype = TEP_FILTER_EXP_MOD;
	} else if (strcmp(token, ">>") == 0) {
		*etype = TEP_FILTER_EXP_RSHIFT;
	} else if (strcmp(token, "<<") == 0) {
		*etype = TEP_FILTER_EXP_LSHIFT;
	} else if (strcmp(token, "&") == 0) {
		*etype = TEP_FILTER_EXP_AND;
	} else if (strcmp(token, "|") == 0) {
		*etype = TEP_FILTER_EXP_OR;
	} else if (strcmp(token, "^") == 0) {
		*etype = TEP_FILTER_EXP_XOR;
	} else if (strcmp(token, "~") == 0)
		*etype = TEP_FILTER_EXP_NOT;

	if (*etype != TEP_FILTER_EXP_NONE)
		return OP_EXP;

	/* Check for compares */
	if (strcmp(token, "==") == 0)
		*ctype = TEP_FILTER_CMP_EQ;
	else if (strcmp(token, "!=") == 0)
		*ctype = TEP_FILTER_CMP_NE;
	else if (strcmp(token, "<") == 0)
		*ctype = TEP_FILTER_CMP_LT;
	else if (strcmp(token, ">") == 0)
		*ctype = TEP_FILTER_CMP_GT;
	else if (strcmp(token, "<=") == 0)
		*ctype = TEP_FILTER_CMP_LE;
	else if (strcmp(token, ">=") == 0)
		*ctype = TEP_FILTER_CMP_GE;
	else if (strcmp(token, "=~") == 0)
		*ctype = TEP_FILTER_CMP_REGEX;
	else if (strcmp(token, "!~") == 0)
		*ctype = TEP_FILTER_CMP_NOT_REGEX;
	else
		return OP_NONE;

	return OP_CMP;
}