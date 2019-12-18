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
 int YY_ID ; 
 scalar_t__ YY_IN_SET (int,int,char*) ; 
 int YY__COMMA ; 
 int YY__LPAREN ; 
 int YY__RPAREN ; 
#define  YY___ATTRIBUTE 135 
#define  YY___ATTRIBUTE__ 134 
#define  YY___CDECL 133 
#define  YY___DECLSPEC 132 
#define  YY___FASTCALL 131 
#define  YY___STDCALL 130 
#define  YY___THISCALL 129 
#define  YY___VECTORCALL 128 
 int /*<<< orphan*/  ZEND_FFI_ABI_CDECL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_FASTCALL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_STDCALL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_THISCALL ; 
 int /*<<< orphan*/  ZEND_FFI_ABI_VECTORCALL ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_assignment_expression (int,int /*<<< orphan*/ *) ; 
 int parse_attrib (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_add_msvc_attribute_value (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_set_abi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_attributes(int sym, zend_ffi_dcl *dcl) {
	const char *name;
	size_t name_len;
	zend_ffi_val val;
	do {
		switch (sym) {
			case YY___ATTRIBUTE:
			case YY___ATTRIBUTE__:
				sym = get_sym();
				if (sym != YY__LPAREN) {
					yy_error_sym("'(' expected, got", sym);
				}
				sym = get_sym();
				if (sym != YY__LPAREN) {
					yy_error_sym("'(' expected, got", sym);
				}
				sym = get_sym();
				sym = parse_attrib(sym, dcl);
				while (sym == YY__COMMA) {
					sym = get_sym();
					sym = parse_attrib(sym, dcl);
				}
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				break;
			case YY___DECLSPEC:
				sym = get_sym();
				if (sym != YY__LPAREN) {
					yy_error_sym("'(' expected, got", sym);
				}
				sym = get_sym();
				do {
					sym = parse_ID(sym, &name, &name_len);
					if (sym == YY__LPAREN) {
						sym = get_sym();
						sym = parse_assignment_expression(sym, &val);
						zend_ffi_add_msvc_attribute_value(dcl, name, name_len, &val);
						if (sym != YY__RPAREN) {
							yy_error_sym("')' expected, got", sym);
						}
						sym = get_sym();
					}
				} while (sym == YY_ID);
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				break;
			case YY___CDECL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_CDECL);
				break;
			case YY___STDCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_STDCALL);
				break;
			case YY___FASTCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_FASTCALL);
				break;
			case YY___THISCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_THISCALL);
				break;
			case YY___VECTORCALL:
				sym = get_sym();
				zend_ffi_set_abi(dcl, ZEND_FFI_ABI_VECTORCALL);
				break;
			default:
				yy_error_sym("unexpected", sym);
		}
	} while (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000"));
	return sym;
}