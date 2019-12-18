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
 int /*<<< orphan*/  YY_CHARACTER ; 
 int /*<<< orphan*/  YY_DECNUMBER ; 
 int /*<<< orphan*/  YY_FLOATNUMBER ; 
 int /*<<< orphan*/  YY_HEXNUMBER ; 
 int /*<<< orphan*/  YY_ID ; 
 scalar_t__ YY_IN_SET (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  YY_OCTNUMBER ; 
 int /*<<< orphan*/  YY_SIZEOF ; 
 int /*<<< orphan*/  YY_STRING ; 
 int /*<<< orphan*/  YY__ALIGNOF ; 
 int /*<<< orphan*/  YY__AND ; 
 int /*<<< orphan*/  YY__BANG ; 
 int YY__COMMA ; 
 int YY__EQUAL ; 
 int YY__LBRACE ; 
 int YY__LBRACK ; 
 int /*<<< orphan*/  YY__LPAREN ; 
 int /*<<< orphan*/  YY__MINUS ; 
 int /*<<< orphan*/  YY__MINUS_MINUS ; 
 int /*<<< orphan*/  YY__PLUS ; 
 int /*<<< orphan*/  YY__PLUS_PLUS ; 
 int YY__POINT ; 
 int YY__RBRACE ; 
 int /*<<< orphan*/  YY__STAR ; 
 int /*<<< orphan*/  YY__TILDE ; 
 int /*<<< orphan*/  YY___ALIGNOF ; 
 int /*<<< orphan*/  YY___ALIGNOF__ ; 
 int get_sym () ; 
 int parse_assignment_expression (int,int /*<<< orphan*/ *) ; 
 int parse_designation (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int yy_line ; 
 unsigned char const* yy_pos ; 
 unsigned char const* yy_text ; 

__attribute__((used)) static int parse_initializer(int sym) {
	int   sym2;
	const unsigned char *save_pos;
	const unsigned char *save_text;
	int   save_line;
	int alt343;
	zend_ffi_val dummy;
	if (sym != YY__EQUAL) {
		yy_error_sym("'=' expected, got", sym);
	}
	sym = get_sym();
	if (YY_IN_SET(sym, (YY__LPAREN,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__STAR,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__), "\010\000\000\000\000\000\001\000\004\030\377\376\000")) {
		sym = parse_assignment_expression(sym, &dummy);
	} else if (sym == YY__LBRACE) {
		sym = get_sym();
		if (sym == YY__LBRACK || sym == YY__POINT) {
			sym = parse_designation(sym);
		}
		sym = parse_initializer(sym);
		while (1) {
			save_pos  = yy_pos;
			save_text = yy_text;
			save_line = yy_line;
			alt343 = -2;
			sym2 = sym;
			if (sym2 == YY__COMMA) {
				sym2 = get_sym();
				goto _yy_state_343_1;
			} else if (sym2 == YY__RBRACE) {
				alt343 = 348;
				goto _yy_state_343;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_343_1:
			if (sym2 == YY__LBRACK || sym2 == YY__POINT || sym2 == YY__EQUAL) {
				alt343 = 344;
				goto _yy_state_343;
			} else if (sym2 == YY__RBRACE) {
				alt343 = 347;
				goto _yy_state_343;
			} else {
				yy_error_sym("unexpected", sym2);
			}
_yy_state_343:
			yy_pos  = save_pos;
			yy_text = save_text;
			yy_line = save_line;
			if (alt343 != 344) {
				break;
			}
			sym = get_sym();
			if (sym == YY__LBRACK || sym == YY__POINT) {
				sym = parse_designation(sym);
			}
			sym = parse_initializer(sym);
		}
		if (alt343 == 347) {
			sym = get_sym();
		}
		if (sym != YY__RBRACE) {
			yy_error_sym("'}' expected, got", sym);
		}
		sym = get_sym();
	} else {
		yy_error_sym("unexpected", sym);
	}
	return sym;
}