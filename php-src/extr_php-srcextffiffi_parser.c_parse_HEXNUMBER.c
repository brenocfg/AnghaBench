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
 int YY_HEXNUMBER ; 
 int get_sym () ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 scalar_t__ yy_pos ; 
 scalar_t__ yy_text ; 
 int /*<<< orphan*/  zend_ffi_val_number (int /*<<< orphan*/ *,int,char const*,scalar_t__) ; 

__attribute__((used)) static int parse_HEXNUMBER(int sym, zend_ffi_val *val) {
	if (sym != YY_HEXNUMBER) {
		yy_error_sym("<HEXNUMBER> expected, got", sym);
	}
	zend_ffi_val_number(val, 16, (const char*)yy_text + 2, yy_pos - yy_text - 2);
	sym = get_sym();
	return sym;
}