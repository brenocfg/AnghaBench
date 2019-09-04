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
 int YY__EQUAL ; 
 int YY__LBRACK ; 
 int YY__POINT ; 
 int YY__RBRACK ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_constant_expression (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 

__attribute__((used)) static int parse_designation(int sym) {
	const char *name;
	size_t name_len;
	zend_ffi_val dummy;
	do {
		if (sym == YY__LBRACK) {
			sym = get_sym();
			sym = parse_constant_expression(sym, &dummy);
			if (sym != YY__RBRACK) {
				yy_error_sym("']' expected, got", sym);
			}
			sym = get_sym();
		} else if (sym == YY__POINT) {
			sym = get_sym();
			sym = parse_ID(sym, &name, &name_len);
		} else {
			yy_error_sym("unexpected", sym);
		}
	} while (sym == YY__LBRACK || sym == YY__POINT);
	if (sym != YY__EQUAL) {
		yy_error_sym("'=' expected, got", sym);
	}
	sym = get_sym();
	return sym;
}