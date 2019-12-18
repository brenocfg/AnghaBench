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
typedef  int /*<<< orphan*/  zend_ffi_val ;

/* Variables and functions */
 int YY__COLON ; 
 int YY__QUERY ; 
 int get_sym () ; 
 int parse_expression (int,int /*<<< orphan*/ *) ; 
 int parse_logical_or_expression (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_expr_conditional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_conditional_expression(int sym, zend_ffi_val *val) {
	zend_ffi_val op2, op3;
	sym = parse_logical_or_expression(sym, val);
	if (sym == YY__QUERY) {
		sym = get_sym();
		sym = parse_expression(sym, &op2);
		if (sym != YY__COLON) {
			yy_error_sym("':' expected, got", sym);
		}
		sym = get_sym();
		sym = parse_conditional_expression(sym, &op3);
		zend_ffi_expr_conditional(val, &op2, &op3);
	}
	return sym;
}