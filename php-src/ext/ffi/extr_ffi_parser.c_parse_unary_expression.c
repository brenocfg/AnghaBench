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
#define  YY_CHARACTER 150 
#define  YY_DECNUMBER 149 
#define  YY_FLOATNUMBER 148 
#define  YY_HEXNUMBER 147 
#define  YY_ID 146 
 int /*<<< orphan*/  YY_IN_SET (int,int const,char*) ; 
#define  YY_OCTNUMBER 145 
#define  YY_SIZEOF 144 
#define  YY_STRING 143 
#define  YY__ALIGNOF 142 
#define  YY__AND 141 
#define  YY__BANG 140 
#define  YY__LBRACK 139 
#define  YY__LPAREN 138 
#define  YY__MINUS 137 
#define  YY__MINUS_GREATER 136 
#define  YY__MINUS_MINUS 135 
#define  YY__PLUS 134 
#define  YY__PLUS_PLUS 133 
#define  YY__POINT 132 
 int YY__RBRACK ; 
 int YY__RPAREN ; 
#define  YY__STAR 131 
#define  YY__TILDE 130 
#define  YY___ALIGNOF 129 
#define  YY___ALIGNOF__ 128 
 int /*<<< orphan*/  ZEND_FFI_ATTR_INIT ; 
 int get_sym () ; 
 int parse_CHARACTER (int,int /*<<< orphan*/ *) ; 
 int parse_DECNUMBER (int,int /*<<< orphan*/ *) ; 
 int parse_FLOATNUMBER (int,int /*<<< orphan*/ *) ; 
 int parse_HEXNUMBER (int,int /*<<< orphan*/ *) ; 
 int parse_ID (int,char const**,size_t*) ; 
 int parse_OCTNUMBER (int,int /*<<< orphan*/ *) ; 
 int parse_STRING (int,int /*<<< orphan*/ *) ; 
 int parse_cast_expression (int,int /*<<< orphan*/ *) ; 
 int parse_expr_list (int) ; 
 int parse_expression (int,int /*<<< orphan*/ *) ; 
 int parse_type_name (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synpred_5 (int) ; 
 int /*<<< orphan*/  synpred_6 (int) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_expr_alignof_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_alignof_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_bool_not (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_bw_not (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_neg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_plus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_sizeof_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_expr_sizeof_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_resolve_const (char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_val_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_unary_expression(int sym, zend_ffi_val *val) {
	const char *name;
	size_t name_len;
	zend_ffi_dcl dcl = ZEND_FFI_ATTR_INIT;
	switch (sym) {
		case YY_ID:
			sym = parse_ID(sym, &name, &name_len);
			zend_ffi_resolve_const(name, name_len, val);
			while (YY_IN_SET(sym, (YY__LBRACK,YY__LPAREN,YY__POINT,YY__MINUS_GREATER,YY__PLUS_PLUS,YY__MINUS_MINUS), "\010\000\000\000\000\000\002\020\000\200\003\000\000")) {
				switch (sym) {
					case YY__LBRACK:
						sym = get_sym();
						sym = parse_expr_list(sym);
						if (sym != YY__RBRACK) {
							yy_error_sym("']' expected, got", sym);
						}
						sym = get_sym();
						break;
					case YY__LPAREN:
						sym = get_sym();
						if (YY_IN_SET(sym, (YY__LPAREN,YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__STAR,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__), "\010\000\000\000\000\000\001\000\004\030\377\376\000")) {
							sym = parse_expr_list(sym);
						}
						if (sym != YY__RPAREN) {
							yy_error_sym("')' expected, got", sym);
						}
						sym = get_sym();
						break;
					case YY__POINT:
						sym = get_sym();
						sym = parse_ID(sym, &name, &name_len);
						break;
					case YY__MINUS_GREATER:
						sym = get_sym();
						sym = parse_ID(sym, &name, &name_len);
						break;
					case YY__PLUS_PLUS:
						sym = get_sym();
						break;
					default:
						sym = get_sym();
						break;
				}
				zend_ffi_val_error(val);
			}
			break;
		case YY_OCTNUMBER:
			sym = parse_OCTNUMBER(sym, val);
			break;
		case YY_DECNUMBER:
			sym = parse_DECNUMBER(sym, val);
			break;
		case YY_HEXNUMBER:
			sym = parse_HEXNUMBER(sym, val);
			break;
		case YY_FLOATNUMBER:
			sym = parse_FLOATNUMBER(sym, val);
			break;
		case YY_STRING:
			sym = parse_STRING(sym, val);
			break;
		case YY_CHARACTER:
			sym = parse_CHARACTER(sym, val);
			break;
		case YY__LPAREN:
			sym = get_sym();
			sym = parse_expression(sym, val);
			if (sym != YY__RPAREN) {
				yy_error_sym("')' expected, got", sym);
			}
			sym = get_sym();
			break;
		case YY__PLUS_PLUS:
			sym = get_sym();
			sym = parse_unary_expression(sym, val);
			zend_ffi_val_error(val);
			break;
		case YY__MINUS_MINUS:
			sym = get_sym();
			sym = parse_unary_expression(sym, val);
			zend_ffi_val_error(val);
			break;
		case YY__AND:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_val_error(val);
			break;
		case YY__STAR:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_val_error(val);
			break;
		case YY__PLUS:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_expr_plus(val);
			break;
		case YY__MINUS:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_expr_neg(val);
			break;
		case YY__TILDE:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_expr_bw_not(val);
			break;
		case YY__BANG:
			sym = get_sym();
			sym = parse_cast_expression(sym, val);
			zend_ffi_expr_bool_not(val);
			break;
		case YY_SIZEOF:
			sym = get_sym();
			if ((sym == YY__LPAREN) && synpred_5(sym)) {
				sym = get_sym();
				sym = parse_type_name(sym, &dcl);
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				zend_ffi_expr_sizeof_type(val, &dcl);
			} else if (YY_IN_SET(sym, (YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__STAR,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__), "\010\000\000\000\000\000\001\000\004\030\377\376\000")) {
				sym = parse_unary_expression(sym, val);
				zend_ffi_expr_sizeof_val(val);
			} else {
				yy_error_sym("unexpected", sym);
			}
			break;
		case YY__ALIGNOF:
			sym = get_sym();
			if (sym != YY__LPAREN) {
				yy_error_sym("'(' expected, got", sym);
			}
			sym = get_sym();
			sym = parse_type_name(sym, &dcl);
			if (sym != YY__RPAREN) {
				yy_error_sym("')' expected, got", sym);
			}
			sym = get_sym();
			zend_ffi_expr_alignof_type(val, &dcl);
			break;
		case YY___ALIGNOF:
		case YY___ALIGNOF__:
			sym = get_sym();
			if ((sym == YY__LPAREN) && synpred_6(sym)) {
				sym = get_sym();
				sym = parse_type_name(sym, &dcl);
				if (sym != YY__RPAREN) {
					yy_error_sym("')' expected, got", sym);
				}
				sym = get_sym();
				zend_ffi_expr_alignof_type(val, &dcl);
			} else if (YY_IN_SET(sym, (YY_ID,YY_OCTNUMBER,YY_DECNUMBER,YY_HEXNUMBER,YY_FLOATNUMBER,YY_STRING,YY_CHARACTER,YY__LPAREN,YY__PLUS_PLUS,YY__MINUS_MINUS,YY__AND,YY__STAR,YY__PLUS,YY__MINUS,YY__TILDE,YY__BANG,YY_SIZEOF,YY__ALIGNOF,YY___ALIGNOF,YY___ALIGNOF__), "\010\000\000\000\000\000\001\000\004\030\377\376\000")) {
				sym = parse_unary_expression(sym, val);
				zend_ffi_expr_alignof_val(val);
			} else {
				yy_error_sym("unexpected", sym);
			}
			break;
		default:
			yy_error_sym("unexpected", sym);
	}
	return sym;
}