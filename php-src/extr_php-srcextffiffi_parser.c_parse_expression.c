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
 int YY__COMMA ; 
 int get_sym () ; 
 int parse_assignment_expression (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_expression(int sym, zend_ffi_val *val) {
	sym = parse_assignment_expression(sym, val);
	while (sym == YY__COMMA) {
		sym = get_sym();
		sym = parse_assignment_expression(sym, val);
	}
	return sym;
}