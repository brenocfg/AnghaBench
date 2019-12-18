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
 int /*<<< orphan*/  YY_AUTO ; 
 int /*<<< orphan*/  YY_CHAR ; 
 int /*<<< orphan*/  YY_COMPLEX ; 
 int /*<<< orphan*/  YY_CONST ; 
 int /*<<< orphan*/  YY_DOUBLE ; 
 int /*<<< orphan*/  YY_ENUM ; 
 int /*<<< orphan*/  YY_EXTERN ; 
 int /*<<< orphan*/  YY_FLOAT ; 
 int YY_ID ; 
 int /*<<< orphan*/  YY_INLINE ; 
 int /*<<< orphan*/  YY_INT ; 
 scalar_t__ YY_IN_SET (int,int,char*) ; 
 int /*<<< orphan*/  YY_LONG ; 
 int /*<<< orphan*/  YY_REGISTER ; 
 int /*<<< orphan*/  YY_RESTRICT ; 
 int /*<<< orphan*/  YY_SHORT ; 
 int /*<<< orphan*/  YY_SIGNED ; 
 int /*<<< orphan*/  YY_STATIC ; 
 int YY_STRING ; 
 int /*<<< orphan*/  YY_STRUCT ; 
 int /*<<< orphan*/  YY_TYPEDEF ; 
 int /*<<< orphan*/  YY_UNION ; 
 int /*<<< orphan*/  YY_UNSIGNED ; 
 int /*<<< orphan*/  YY_VOID ; 
 int /*<<< orphan*/  YY_VOLATILE ; 
 int /*<<< orphan*/  YY__ALIGNAS ; 
 int /*<<< orphan*/  YY__ATOMIC ; 
 int /*<<< orphan*/  YY__BOOL ; 
 int YY__COMMA ; 
 int /*<<< orphan*/  YY__COMPLEX ; 
 int YY__EQUAL ; 
 int YY__LPAREN ; 
 int /*<<< orphan*/  YY__NORETURN ; 
 int YY__RPAREN ; 
 int YY__SEMICOLON ; 
 int YY__STAR ; 
 int YY___ASM__ ; 
 int YY___ATTRIBUTE ; 
 int /*<<< orphan*/  YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___CDECL ; 
 int /*<<< orphan*/  YY___COMPLEX ; 
 int /*<<< orphan*/  YY___COMPLEX__ ; 
 int /*<<< orphan*/  YY___CONST ; 
 int /*<<< orphan*/  YY___CONST__ ; 
 int /*<<< orphan*/  YY___DECLSPEC ; 
 int YY___EXTENSION__ ; 
 int /*<<< orphan*/  YY___FASTCALL ; 
 int /*<<< orphan*/  YY___INLINE ; 
 int /*<<< orphan*/  YY___INLINE__ ; 
 int /*<<< orphan*/  YY___RESTRICT ; 
 int /*<<< orphan*/  YY___RESTRICT__ ; 
 int /*<<< orphan*/  YY___STDCALL ; 
 int /*<<< orphan*/  YY___THISCALL ; 
 int /*<<< orphan*/  YY___VECTORCALL ; 
 int /*<<< orphan*/  YY___VOLATILE ; 
 int /*<<< orphan*/  YY___VOLATILE__ ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_INIT ; 
 int get_sym () ; 
 int parse_STRING (int,int /*<<< orphan*/ *) ; 
 int parse_attributes (int,int /*<<< orphan*/ *) ; 
 int parse_declaration_specifiers (int,int /*<<< orphan*/ *) ; 
 int parse_declarator (int,int /*<<< orphan*/ *,char const**,size_t*) ; 
 int parse_initializer (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_declare (char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_declarations(int sym) {
	while (YY_IN_SET(sym, (YY___EXTENSION__,YY_TYPEDEF,YY_EXTERN,YY_STATIC,YY_AUTO,YY_REGISTER,YY_INLINE,YY___INLINE,YY___INLINE__,YY__NORETURN,YY__ALIGNAS,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID), "\202\377\377\377\377\107\360\017\000\000\000\002\000")) {
		zend_ffi_dcl common_dcl = ZEND_FFI_ATTR_INIT;
		if (sym == YY___EXTENSION__) {
			sym = get_sym();
		}
		sym = parse_declaration_specifiers(sym, &common_dcl);
		if (sym == YY__STAR || sym == YY_ID || sym == YY__LPAREN) {
			const char *name;
			size_t name_len;
			zend_ffi_dcl dcl;
			dcl = common_dcl;
			sym = parse_declarator(sym, &dcl, &name, &name_len);
			if (sym == YY___ASM__) {
				zend_ffi_val asm_str;
				sym = get_sym();
				if (sym != YY__LPAREN) {
					yy_error_sym("'(' expected, got", sym);
				}
				sym = get_sym();
				do {
					sym = parse_STRING(sym, &asm_str);
				} while (sym == YY_STRING);
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
			}
			if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
				sym = parse_attributes(sym, &dcl);
			}
			if (sym == YY__EQUAL) {
				sym = parse_initializer(sym);
			}
			zend_ffi_declare(name, name_len, &dcl);
			while (sym == YY__COMMA) {
				sym = get_sym();
				dcl = common_dcl;
				sym = parse_declarator(sym, &dcl, &name, &name_len);
				if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
					sym = parse_attributes(sym, &dcl);
				}
				if (sym == YY__EQUAL) {
					sym = parse_initializer(sym);
				}
				zend_ffi_declare(name, name_len, &dcl);
			}
		}
		if (sym != YY__SEMICOLON) {
			yy_error_sym("';' expected, got", sym);
		}
		sym = get_sym();
	}
	return sym;
}