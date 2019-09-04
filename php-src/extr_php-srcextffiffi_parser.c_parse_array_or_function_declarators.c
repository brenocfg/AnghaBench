#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ zend_ffi_val ;
struct TYPE_11__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_2__ zend_ffi_dcl ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  YY_CHAR ; 
 int /*<<< orphan*/  YY_CHARACTER ; 
 int /*<<< orphan*/  YY_COMPLEX ; 
 int YY_CONST ; 
 int /*<<< orphan*/  YY_DECNUMBER ; 
 int /*<<< orphan*/  YY_DOUBLE ; 
 int /*<<< orphan*/  YY_ENUM ; 
 int /*<<< orphan*/  YY_FLOAT ; 
 int /*<<< orphan*/  YY_FLOATNUMBER ; 
 int /*<<< orphan*/  YY_HEXNUMBER ; 
 int /*<<< orphan*/  YY_ID ; 
 int /*<<< orphan*/  YY_INT ; 
 scalar_t__ YY_IN_SET (int,int,char*) ; 
 int /*<<< orphan*/  YY_LONG ; 
 int /*<<< orphan*/  YY_OCTNUMBER ; 
 int /*<<< orphan*/  YY_RESTRICT ; 
 int /*<<< orphan*/  YY_SHORT ; 
 int /*<<< orphan*/  YY_SIGNED ; 
 int /*<<< orphan*/  YY_SIZEOF ; 
 int YY_STATIC ; 
 int /*<<< orphan*/  YY_STRING ; 
 int /*<<< orphan*/  YY_STRUCT ; 
 int /*<<< orphan*/  YY_UNION ; 
 int /*<<< orphan*/  YY_UNSIGNED ; 
 int /*<<< orphan*/  YY_VOID ; 
 int /*<<< orphan*/  YY_VOLATILE ; 
 int /*<<< orphan*/  YY__ALIGNOF ; 
 int /*<<< orphan*/  YY__AND ; 
 int /*<<< orphan*/  YY__ATOMIC ; 
 int /*<<< orphan*/  YY__BANG ; 
 int /*<<< orphan*/  YY__BOOL ; 
 int YY__COMMA ; 
 int /*<<< orphan*/  YY__COMPLEX ; 
 int YY__LBRACK ; 
 int YY__LPAREN ; 
 int /*<<< orphan*/  YY__MINUS ; 
 int /*<<< orphan*/  YY__MINUS_MINUS ; 
 int /*<<< orphan*/  YY__PLUS ; 
 int /*<<< orphan*/  YY__PLUS_PLUS ; 
 int YY__POINT_POINT_POINT ; 
 int YY__RBRACK ; 
 int YY__RPAREN ; 
 int YY__STAR ; 
 int /*<<< orphan*/  YY__TILDE ; 
 int /*<<< orphan*/  YY___ALIGNOF ; 
 int /*<<< orphan*/  YY___ALIGNOF__ ; 
 int /*<<< orphan*/  YY___ATTRIBUTE ; 
 int /*<<< orphan*/  YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___COMPLEX ; 
 int /*<<< orphan*/  YY___COMPLEX__ ; 
 int /*<<< orphan*/  YY___CONST ; 
 int /*<<< orphan*/  YY___CONST__ ; 
 int /*<<< orphan*/  YY___DECLSPEC ; 
 int YY___EXTENSION__ ; 
 int /*<<< orphan*/  YY___RESTRICT ; 
 int /*<<< orphan*/  YY___RESTRICT__ ; 
 int /*<<< orphan*/  YY___VOLATILE ; 
 int /*<<< orphan*/  YY___VOLATILE__ ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_INCOMPLETE_ARRAY ; 
 TYPE_2__ ZEND_FFI_ATTR_INIT ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_VARIADIC ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_VLA ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_EMPTY ; 
 int get_sym () ; 
 int parse_assignment_expression (int,TYPE_1__*) ; 
 int parse_parameter_declaration (int,int /*<<< orphan*/ **) ; 
 int parse_type_qualifier_list (int,TYPE_2__*) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int yy_line ; 
 unsigned char const* yy_pos ; 
 unsigned char const* yy_text ; 
 int /*<<< orphan*/  zend_ffi_make_array_type (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ffi_make_func_type (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_array_or_function_declarators(int sym, zend_ffi_dcl *dcl) {
	int   sym2;
	const unsigned char *save_pos;
	const unsigned char *save_text;
	int   save_line;
	int alt104;
	int alt100;
	int alt114;
	zend_ffi_dcl dummy = ZEND_FFI_ATTR_INIT;
	zend_ffi_val len = {.kind = ZEND_FFI_VAL_EMPTY};
	HashTable *args = NULL;
	uint32_t attr = 0;
	if (sym == YY__LBRACK) {
		sym = get_sym();
		save_pos  = yy_pos;
		save_text = yy_text;
		save_line = yy_line;
		alt100 = -2;
		sym2 = sym;
		if (sym2 == YY_STATIC) {
			alt100 = 101;
			goto _yy_state_100;
		} else if (YY_IN_SET(sym2, (YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\000\000\340\177\000\000\000\007\000\000\000\000\000")) {
			alt100 = 104;
			goto _yy_state_100;
		} else if (sym2 == YY__STAR) {
			sym2 = get_sym();
			goto _yy_state_100_15;
		} else if (YY_IN_SET(sym2, (YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER), "\010\000\000\000\000\000\000\000\002\214\177\177\000")) {
			alt100 = 110;
			goto _yy_state_100;
		} else if (sym2 == YY__RBRACK) {
			alt100 = 111;
			goto _yy_state_100;
		} else {
			yy_error_sym("unexpected", sym2);
		}
_yy_state_100_15:
		if (sym2 == YY__RBRACK) {
			alt100 = 109;
			goto _yy_state_100;
		} else if (YY_IN_SET(sym2, (YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__STAR), "\010\000\000\000\000\000\020\000\002\214\177\177\000")) {
			alt100 = 110;
			goto _yy_state_100;
		} else {
			yy_error_sym("unexpected", sym2);
		}
_yy_state_100:
		yy_pos  = save_pos;
		yy_text = save_text;
		yy_line = save_line;
		if (alt100 == 101) {
			sym = get_sym();
			if (YY_IN_SET(sym, (YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\000\000\340\177\000\000\000\007\000\000\000\000\000")) {
				sym = parse_type_qualifier_list(sym, &dummy);
			}
			sym = parse_assignment_expression(sym, &len);
		} else if (alt100 == 104) {
			sym = parse_type_qualifier_list(sym, &dummy);
			save_pos  = yy_pos;
			save_text = yy_text;
			save_line = yy_line;
			alt104 = -2;
			sym2 = sym;
			if (sym2 == YY_STATIC) {
				alt104 = 105;
				goto _yy_state_104;
			} else if (sym2 == YY__STAR) {
				sym2 = get_sym();
				goto _yy_state_104_2;
			} else if (YY_IN_SET(sym2, (YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER), "\010\000\000\000\000\000\000\000\002\214\177\177\000")) {
				alt104 = 108;
				goto _yy_state_104;
			} else if (sym2 == YY__RBRACK) {
				alt104 = 111;
				goto _yy_state_104;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_104_2:
			if (sym2 == YY__RBRACK) {
				alt104 = 107;
				goto _yy_state_104;
			} else if (YY_IN_SET(sym2, (YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__STAR), "\010\000\000\000\000\000\020\000\002\214\177\177\000")) {
				alt104 = 108;
				goto _yy_state_104;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_104:
			yy_pos  = save_pos;
			yy_text = save_text;
			yy_line = save_line;
			if (alt104 == 105) {
				sym = get_sym();
				sym = parse_assignment_expression(sym, &len);
			} else if (alt104 == 111) {
				attr |= ZEND_FFI_ATTR_INCOMPLETE_ARRAY;
			} else if (alt104 == 107) {
				sym = get_sym();
				attr |= ZEND_FFI_ATTR_VLA;
			} else if (alt104 == 108) {
				sym = parse_assignment_expression(sym, &len);
			} else {
				yy_error_sym("unexpected", sym);
			}
		} else if (alt100 == 111 || alt100 == 109 || alt100 == 110) {
			if (alt100 == 111) {
				attr |= ZEND_FFI_ATTR_INCOMPLETE_ARRAY;
			} else if (alt100 == 109) {
				sym = get_sym();
				attr |= ZEND_FFI_ATTR_VLA;
			} else {
				sym = parse_assignment_expression(sym, &len);
			}
		} else {
			yy_error_sym("unexpected", sym);
		}
		if (sym != YY__RBRACK) {
			yy_error_sym("']' expected, got", sym);
		}
		sym = get_sym();
		if (sym == YY__LBRACK || sym == YY__LPAREN) {
			sym = parse_array_or_function_declarators(sym, dcl);
		}
		dcl->attr |= attr;
		zend_ffi_make_array_type(dcl, &len);
	} else if (sym == YY__LPAREN) {
		sym = get_sym();
		if (YY_IN_SET(sym, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY__POINT_POINT_POINT), "\002\000\340\377\377\177\204\007\000\000\000\001\000")) {
			if (YY_IN_SET(sym, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\002\000\340\377\377\177\004\007\000\000\000\001\000")) {
				sym = parse_parameter_declaration(sym, &args);
				while (1) {
					save_pos  = yy_pos;
					save_text = yy_text;
					save_line = yy_line;
					alt114 = -2;
					sym2 = sym;
					if (sym2 == YY__COMMA) {
						sym2 = get_sym();
						goto _yy_state_114_1;
					} else if (sym2 == YY__RPAREN) {
						alt114 = 120;
						goto _yy_state_114;
					} else {
						yy_error_sym("unexpected", sym2);
					}
_yy_state_114_1:
					if (YY_IN_SET(sym2, (YY___EXTENSION__,YY_VOID,YY_CHAR,YY_SHORT,YY_INT,YY_LONG,YY_FLOAT,YY_DOUBLE,YY_SIGNED,YY_UNSIGNED,YY__BOOL,YY__COMPLEX,YY_COMPLEX,YY___COMPLEX,YY___COMPLEX__,YY_STRUCT,YY_UNION,YY_ENUM,YY_ID,YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\002\000\340\377\377\177\004\007\000\000\000\001\000")) {
						alt114 = 115;
						goto _yy_state_114;
					} else if (sym2 == YY__POINT_POINT_POINT) {
						alt114 = 117;
						goto _yy_state_114;
					} else {
						yy_error_sym("unexpected", sym2);
					}
_yy_state_114:
					yy_pos  = save_pos;
					yy_text = save_text;
					yy_line = save_line;
					if (alt114 != 115) {
						break;
					}
					sym = get_sym();
					sym = parse_parameter_declaration(sym, &args);
				}
				if (alt114 == 117) {
					sym = get_sym();
					if (sym != YY__POINT_POINT_POINT) {
						yy_error_sym("'...' expected, got", sym);
					}
					sym = get_sym();
					attr |= ZEND_FFI_ATTR_VARIADIC;
				}
			} else {
				sym = get_sym();
				attr |= ZEND_FFI_ATTR_VARIADIC;
			}
		}
		if (sym != YY__RPAREN) {
			yy_error_sym("')' expected, got", sym);
		}
		sym = get_sym();
		if (sym == YY__LBRACK || sym == YY__LPAREN) {
			sym = parse_array_or_function_declarators(sym, dcl);
		}
		dcl->attr |= attr;
		zend_ffi_make_func_type(dcl, args);
	} else {
		yy_error_sym("unexpected", sym);
	}
	return sym;
}