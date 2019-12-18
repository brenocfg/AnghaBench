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
 int YY__PERCENT ; 
 int YY__SLASH ; 
 int YY__STAR ; 
 int get_sym () ; 
 int parse_cast_expression (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_multiplicative_expression(int sym, zend_ffi_val *val) {
	zend_ffi_val op2;
	sym = parse_cast_expression(sym, val);
	while (sym == YY__STAR || sym == YY__SLASH || sym == YY__PERCENT) {
		if (sym == YY__STAR) {
			sym = get_sym();
			sym = parse_cast_expression(sym, &op2);
			zend_ffi_expr_mul(val, &op2);
		} else if (sym == YY__SLASH) {
			sym = get_sym();
			sym = parse_cast_expression(sym, &op2);
			zend_ffi_expr_div(val, &op2);
		} else {
			sym = get_sym();
			sym = parse_cast_expression(sym, &op2);
			zend_ffi_expr_mod(val, &op2);
		}
	}
	return sym;
}