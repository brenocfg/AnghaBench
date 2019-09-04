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
 int YY__COLON ; 
 int /*<<< orphan*/  YY__COMMA ; 
 int YY__LPAREN ; 
 int /*<<< orphan*/  YY__RBRACE ; 
 int /*<<< orphan*/  YY__SEMICOLON ; 
 int YY__STAR ; 
 int YY___ATTRIBUTE ; 
 int YY___ATTRIBUTE__ ; 
 int YY___DECLSPEC ; 
 int get_sym () ; 
 int parse_attributes (int,int /*<<< orphan*/ *) ; 
 int parse_constant_expression (int,int /*<<< orphan*/ *) ; 
 int parse_declarator (int,int /*<<< orphan*/ *,char const**,size_t*) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_add_bit_field (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_add_field (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_struct_declarator(int sym, zend_ffi_dcl *struct_dcl, zend_ffi_dcl *field_dcl) {
	const char *name = NULL;
	size_t name_len = 0;
	zend_ffi_val bits;
	if (sym == YY__STAR || sym == YY_ID || sym == YY__LPAREN) {
		sym = parse_declarator(sym, field_dcl, &name, &name_len);
		if (sym == YY__COLON) {
			sym = get_sym();
			sym = parse_constant_expression(sym, &bits);
			if (sym == YY___ATTRIBUTE || sym == YY___ATTRIBUTE__ || sym == YY___DECLSPEC) {
				sym = parse_attributes(sym, field_dcl);
			}
			zend_ffi_add_bit_field(struct_dcl, name, name_len, field_dcl, &bits);
		} else if (YY_IN_SET(sym, (YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC,YY__COMMA,YY__SEMICOLON,YY__RBRACE), "\140\000\000\000\000\000\001\007\000\000\000\000\000")) {
			if (sym == YY___ATTRIBUTE || sym == YY___ATTRIBUTE__ || sym == YY___DECLSPEC) {
				sym = parse_attributes(sym, field_dcl);
			}
			zend_ffi_add_field(struct_dcl, name, name_len, field_dcl);
		} else {
			yy_error_sym("unexpected", sym);
		}
	} else if (sym == YY__COLON) {
		sym = get_sym();
		sym = parse_constant_expression(sym, &bits);
		zend_ffi_add_bit_field(struct_dcl, NULL, 0, field_dcl, &bits);
	} else {
		yy_error_sym("unexpected", sym);
	}
	return sym;
}