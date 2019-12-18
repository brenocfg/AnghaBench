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
typedef  int /*<<< orphan*/  zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  YY_CHAR ; 
 int /*<<< orphan*/  YY_COMPLEX ; 
 int /*<<< orphan*/  YY_CONST ; 
 int /*<<< orphan*/  YY_DOUBLE ; 
 int /*<<< orphan*/  YY_ENUM ; 
 int /*<<< orphan*/  YY_FLOAT ; 
 int /*<<< orphan*/  YY_ID ; 
 int /*<<< orphan*/  YY_INT ; 
 scalar_t__ YY_IN_SET (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  YY_LONG ; 
 int /*<<< orphan*/  YY_RESTRICT ; 
 int /*<<< orphan*/  YY_SHORT ; 
 int /*<<< orphan*/  YY_SIGNED ; 
 int /*<<< orphan*/  YY_STRUCT ; 
 int /*<<< orphan*/  YY_UNION ; 
 int /*<<< orphan*/  YY_UNSIGNED ; 
 int /*<<< orphan*/  YY_VOID ; 
 int /*<<< orphan*/  YY_VOLATILE ; 
 int /*<<< orphan*/  YY__ATOMIC ; 
 int /*<<< orphan*/  YY__BOOL ; 
 int /*<<< orphan*/  YY__COMPLEX ; 
 int YY__LBRACE ; 
 int YY__RBRACE ; 
 int YY__SEMICOLON ; 
 int /*<<< orphan*/  YY___ATTRIBUTE ; 
 int /*<<< orphan*/  YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___CDECL ; 
 int /*<<< orphan*/  YY___COMPLEX ; 
 int /*<<< orphan*/  YY___COMPLEX__ ; 
 int /*<<< orphan*/  YY___CONST ; 
 int /*<<< orphan*/  YY___CONST__ ; 
 int /*<<< orphan*/  YY___DECLSPEC ; 
 int /*<<< orphan*/  YY___EXTENSION__ ; 
 int /*<<< orphan*/  YY___FASTCALL ; 
 int /*<<< orphan*/  YY___RESTRICT ; 
 int /*<<< orphan*/  YY___RESTRICT__ ; 
 int /*<<< orphan*/  YY___STDCALL ; 
 int /*<<< orphan*/  YY___THISCALL ; 
 int /*<<< orphan*/  YY___VECTORCALL ; 
 int /*<<< orphan*/  YY___VOLATILE ; 
 int /*<<< orphan*/  YY___VOLATILE__ ; 
 int get_sym () ; 
 int parse_attributes (int,int /*<<< orphan*/ *) ; 
 int parse_struct_declaration (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int yy_line ; 
 unsigned char const* yy_pos ; 
 unsigned char const* yy_text ; 
 int /*<<< orphan*/  zend_ffi_adjust_struct_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_struct_contents(int sym, zend_ffi_dcl *dcl) {
	int   sym2;
	const unsigned char *save_pos;
	const unsigned char *save_text;
	int   save_line;
	int alt2;
	if (sym != YY__LBRACE) {
		yy_error_sym("'{' expected, got", sym);
	}
	sym = get_sym();
	if (YY_IN_SET(sym, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\002\000\376\377\377\107\360\017\000\000\000\002\000")) {
		sym = parse_struct_declaration(sym, dcl);
		while (1) {
			save_pos  = yy_pos;
			save_text = yy_text;
			save_line = yy_line;
			alt2 = -2;
			sym2 = sym;
			if (sym2 == YY__SEMICOLON) {
				sym2 = get_sym();
				goto _yy_state_2_1;
			} else if (sym2 == YY__RBRACE) {
				alt2 = 6;
				goto _yy_state_2;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_2_1:
			if (YY_IN_SET(sym2, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\002\000\376\377\377\107\360\017\000\000\000\002\000")) {
				alt2 = 3;
				goto _yy_state_2;
			} else if (sym2 == YY__RBRACE) {
				alt2 = 5;
				goto _yy_state_2;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_2:
			yy_pos  = save_pos;
			yy_text = save_text;
			yy_line = save_line;
			if (alt2 != 3) {
				break;
			}
			sym = get_sym();
			sym = parse_struct_declaration(sym, dcl);
		}
		if (alt2 == 5) {
			sym = get_sym();
		}
	}
	if (sym != YY__RBRACE) {
		yy_error_sym("'}' expected, got", sym);
	}
	sym = get_sym();
	if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY___CDECL,YY___STDCALL,YY___FASTCALL,YY___THISCALL,YY___VECTORCALL), "\000\000\000\000\000\000\360\017\000\000\000\000\000")) {
		sym = parse_attributes(sym, dcl);
	}
	zend_ffi_adjust_struct_size(dcl);
	return sym;
}