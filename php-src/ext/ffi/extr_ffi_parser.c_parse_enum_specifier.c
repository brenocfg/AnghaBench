#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  YY_AUTO ; 
 int /*<<< orphan*/  YY_CHAR ; 
 int /*<<< orphan*/  YY_COMPLEX ; 
 int /*<<< orphan*/  YY_CONST ; 
 int /*<<< orphan*/  YY_DOUBLE ; 
 int YY_ENUM ; 
 int /*<<< orphan*/  YY_EOF ; 
 int /*<<< orphan*/  YY_EXTERN ; 
 int /*<<< orphan*/  YY_FLOAT ; 
 int YY_ID ; 
 int /*<<< orphan*/  YY_INLINE ; 
 int /*<<< orphan*/  YY_INT ; 
 scalar_t__ YY_IN_SET (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  YY_LONG ; 
 int /*<<< orphan*/  YY_REGISTER ; 
 int /*<<< orphan*/  YY_RESTRICT ; 
 int /*<<< orphan*/  YY_SHORT ; 
 int /*<<< orphan*/  YY_SIGNED ; 
 int /*<<< orphan*/  YY_STATIC ; 
 int /*<<< orphan*/  YY_STRUCT ; 
 int /*<<< orphan*/  YY_TYPEDEF ; 
 int /*<<< orphan*/  YY_UNION ; 
 int /*<<< orphan*/  YY_UNSIGNED ; 
 int /*<<< orphan*/  YY_VOID ; 
 int /*<<< orphan*/  YY_VOLATILE ; 
 int /*<<< orphan*/  YY__ALIGNAS ; 
 int /*<<< orphan*/  YY__ATOMIC ; 
 int /*<<< orphan*/  YY__BOOL ; 
 int /*<<< orphan*/  YY__COLON ; 
 int /*<<< orphan*/  YY__COMMA ; 
 int /*<<< orphan*/  YY__COMPLEX ; 
 int YY__LBRACE ; 
 int /*<<< orphan*/  YY__LBRACK ; 
 int /*<<< orphan*/  YY__LPAREN ; 
 int /*<<< orphan*/  YY__NORETURN ; 
 int YY__RBRACE ; 
 int /*<<< orphan*/  YY__RPAREN ; 
 int /*<<< orphan*/  YY__SEMICOLON ; 
 int /*<<< orphan*/  YY__STAR ; 
 int /*<<< orphan*/  YY___ATTRIBUTE ; 
 int /*<<< orphan*/  YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___CDECL ; 
 int /*<<< orphan*/  YY___COMPLEX ; 
 int /*<<< orphan*/  YY___COMPLEX__ ; 
 int /*<<< orphan*/  YY___CONST ; 
 int /*<<< orphan*/  YY___CONST__ ; 
 int /*<<< orphan*/  YY___DECLSPEC ; 
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
 int /*<<< orphan*/  ZEND_FFI_DCL_ENUM ; 
 int get_sym () ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_attributes (int,TYPE_1__*) ; 
 int parse_enumerator_list (int,TYPE_1__*) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_declare_tag (char const*,size_t,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_ffi_make_enum_type (TYPE_1__*) ; 

__attribute__((used)) static int parse_enum_specifier(int sym, zend_ffi_dcl *dcl) {
	if (sym != YY_ENUM) {
		yy_error_sym("'enum' expected, got", sym);
	}
	sym = get_sym();
	dcl->flags |= ZEND_FFI_DCL_ENUM;
	if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
		sym = parse_attributes(sym, dcl);
	}
	if (sym == YY_ID) {
		const char *name;
		size_t name_len;
		sym = parse_ID(sym, &name, &name_len);
		if (sym == YY__LBRACE) {
			zend_ffi_declare_tag(name, name_len, dcl, 0);
			sym = get_sym();
			sym = parse_enumerator_list(sym, dcl);
			if (sym != YY__RBRACE) {
				yy_error_sym("'}' expected, got", sym);
			}
			sym = get_sym();
			if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
				sym = parse_attributes(sym, dcl);
			}
		} else if (YY_IN_SET(sym, (YY_TYPEDEF,YY_EXTERN,YY_STATIC,YY_AUTO,YY_REGISTER,YY_INLINE,YY___INLINE,YY___INLINE__,YY__NORETURN,YY__ALIGNAS,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY__STAR,YY__LPAREN,YY__SEMICOLON,YY__COLON,YY__LBRACK,YY__RBRACE,YY__COMMA,YY__RPAREN,YY_EOF), "\371\377\377\377\377\167\363\017\000\000\000\002\000")) {
			zend_ffi_declare_tag(name, name_len, dcl, 1);
		} else {
			yy_error_sym("unexpected", sym);
		}
	} else if (sym == YY__LBRACE) {
		sym = get_sym();
		zend_ffi_make_enum_type(dcl);
		sym = parse_enumerator_list(sym, dcl);
		if (sym != YY__RBRACE) {
			yy_error_sym("'}' expected, got", sym);
		}
		sym = get_sym();
		if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
			sym = parse_attributes(sym, dcl);
		}
	} else {
		yy_error_sym("unexpected", sym);
	}
	return sym;
}