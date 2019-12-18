#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ zend_ffi_val ;
typedef  int /*<<< orphan*/  zend_ffi_dcl ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int YY__EQUAL ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_EMPTY ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_constant_expression (int,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ffi_add_enum_val (int /*<<< orphan*/ *,char const*,size_t,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_enumerator(int sym, zend_ffi_dcl *enum_dcl, int64_t *min, int64_t *max, int64_t *last) {
	const char *name;
	size_t name_len;
	zend_ffi_val val = {.kind = ZEND_FFI_VAL_EMPTY};
	sym = parse_ID(sym, &name, &name_len);
	if (sym == YY__EQUAL) {
		sym = get_sym();
		sym = parse_constant_expression(sym, &val);
	}
	zend_ffi_add_enum_val(enum_dcl, name, name_len, &val, min, max, last);
	return sym;
}