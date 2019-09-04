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
 int YY__BAR ; 
 int get_sym () ; 
 int parse_exclusive_or_expression (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_bw_or (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_inclusive_or_expression(int sym, zend_ffi_val *val) {
	zend_ffi_val op2;
	sym = parse_exclusive_or_expression(sym, val);
	while (sym == YY__BAR) {
		sym = get_sym();
		sym = parse_exclusive_or_expression(sym, &op2);
		zend_ffi_expr_bw_or(val, &op2);
	}
	return sym;
}