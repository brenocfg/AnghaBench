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
typedef  int /*<<< orphan*/  zend_ffi_dcl ;

/* Variables and functions */
 int YY__LPAREN ; 
 int YY__RPAREN ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_INIT ; 
 int get_sym () ; 
 int parse_type_name (int,int /*<<< orphan*/ *) ; 
 int parse_unary_expression (int,int /*<<< orphan*/ *) ; 
 scalar_t__ synpred_4 (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_expr_cast (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_cast_expression(int sym, zend_ffi_val *val) {
	int do_cast = 0;
	zend_ffi_dcl dcl = ZEND_FFI_ATTR_INIT;
	if ((sym == YY__LPAREN) && synpred_4(sym)) {
		sym = get_sym();
		sym = parse_type_name(sym, &dcl);
		if (sym != YY__RPAREN) {
			yy_error_sym("')' expected, got", sym);
		}
		sym = get_sym();
		do_cast = 1;
	}
	sym = parse_unary_expression(sym, val);
	if (do_cast) zend_ffi_expr_cast(val, &dcl);
	return sym;
}