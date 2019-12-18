#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zend_ffi_dcl ;
typedef  int zend_bool ;

/* Variables and functions */
 int YY_ID ; 
 scalar_t__ YY_IN_SET (int,int /*<<< orphan*/ ,char*) ; 
 int YY__COMMA ; 
 int YY__LBRACK ; 
 int YY__LPAREN ; 
 int YY__RPAREN ; 
 int YY__STAR ; 
 int /*<<< orphan*/  YY___ATTRIBUTE ; 
 int /*<<< orphan*/  YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___CDECL ; 
 int /*<<< orphan*/  YY___DECLSPEC ; 
 int /*<<< orphan*/  YY___FASTCALL ; 
 int /*<<< orphan*/  YY___STDCALL ; 
 int /*<<< orphan*/  YY___THISCALL ; 
 int /*<<< orphan*/  YY___VECTORCALL ; 
 int /*<<< orphan*/  ZEND_FFI_DCL_CHAR ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_array_or_function_declarators (int,TYPE_1__*,TYPE_1__*) ; 
 int parse_attributes (int,TYPE_1__*) ; 
 int parse_pointer (int,TYPE_1__*) ; 
 scalar_t__ synpred_3 (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_nested_declaration (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int parse_parameter_declarator(int sym, zend_ffi_dcl *dcl, const char **name, size_t *name_len) {
	zend_ffi_dcl nested_dcl = {ZEND_FFI_DCL_CHAR, 0, 0, 0, NULL};
	zend_bool nested = 0;
	if (sym == YY__STAR) {
		sym = parse_pointer(sym, dcl);
	}
	if ((sym == YY__LPAREN) && synpred_3(sym)) {
		sym = get_sym();
		if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
			sym = parse_attributes(sym, &nested_dcl);
		}
		sym = parse_parameter_declarator(sym, &nested_dcl, name, name_len);
		if (sym != YY__RPAREN) {
			yy_error_sym("')' expected, got", sym);
		}
		sym = get_sym();
		nested = 1;
	} else if (sym == YY_ID) {
		sym = parse_ID(sym, name, name_len);
	} else if (sym == YY__LBRACK || sym == YY__LPAREN || sym == YY__RPAREN || sym == YY__COMMA) {
	} else {
		yy_error_sym("unexpected", sym);
	}
	if (sym == YY__LBRACK || sym == YY__LPAREN) {
		sym = parse_array_or_function_declarators(sym, dcl, &nested_dcl);
	}
	if (nested) zend_ffi_nested_declaration(dcl, &nested_dcl);
	return sym;
}