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
 int YY_ID ; 
 int YY__COLON ; 
 int YY__COMMA ; 
 int YY__LPAREN ; 
 int YY__RBRACE ; 
 int YY__SEMICOLON ; 
 int YY__STAR ; 
 int YY___ATTRIBUTE ; 
 int YY___ATTRIBUTE__ ; 
 int YY___DECLSPEC ; 
 int /*<<< orphan*/  ZEND_FFI_ATTR_INIT ; 
 int get_sym () ; 
 int parse_attributes (int,int /*<<< orphan*/ *) ; 
 int parse_specifier_qualifier_list (int,int /*<<< orphan*/ *) ; 
 int parse_struct_declarator (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 
 int /*<<< orphan*/  zend_ffi_add_anonymous_field (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_struct_declaration(int sym, zend_ffi_dcl *struct_dcl) {
	zend_ffi_dcl common_field_dcl = ZEND_FFI_ATTR_INIT;
	sym = parse_specifier_qualifier_list(sym, &common_field_dcl);
	if (sym == YY__SEMICOLON || sym == YY__RBRACE) {
		zend_ffi_add_anonymous_field(struct_dcl, &common_field_dcl);
	} else if (sym == YY__STAR || sym == YY_ID || sym == YY__LPAREN || sym == YY__COLON) {
		sym = parse_struct_declarator(sym, struct_dcl, &common_field_dcl);
		while (sym == YY__COMMA) {
			sym = get_sym();
			zend_ffi_dcl field_dcl = common_field_dcl;
			if (sym == YY___ATTRIBUTE || sym == YY___ATTRIBUTE__ || sym == YY___DECLSPEC) {
				sym = parse_attributes(sym, &field_dcl);
			}
			sym = parse_struct_declarator(sym, struct_dcl, &field_dcl);
		}
	} else {
		yy_error_sym("unexpected", sym);
	}
	return sym;
}