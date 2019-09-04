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
 int /*<<< orphan*/  YY_CONST ; 
 scalar_t__ YY_IN_SET (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  YY_RESTRICT ; 
 int /*<<< orphan*/  YY_VOLATILE ; 
 int /*<<< orphan*/  YY__ATOMIC ; 
 int YY___ATTRIBUTE ; 
 int YY___ATTRIBUTE__ ; 
 int /*<<< orphan*/  YY___CONST ; 
 int /*<<< orphan*/  YY___CONST__ ; 
 int YY___DECLSPEC ; 
 int /*<<< orphan*/  YY___RESTRICT ; 
 int /*<<< orphan*/  YY___RESTRICT__ ; 
 int /*<<< orphan*/  YY___VOLATILE ; 
 int /*<<< orphan*/  YY___VOLATILE__ ; 
 int parse_attributes (int,int /*<<< orphan*/ *) ; 
 int parse_type_qualifier (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yy_error_sym (char*,int) ; 

__attribute__((used)) static int parse_type_qualifier_list(int sym, zend_ffi_dcl *dcl) {
	do {
		if (YY_IN_SET(sym, (YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC), "\000\000\340\177\000\000\000\000\000\000\000\000\000")) {
			sym = parse_type_qualifier(sym, dcl);
		} else if (sym == YY___ATTRIBUTE || sym == YY___ATTRIBUTE__ || sym == YY___DECLSPEC) {
			sym = parse_attributes(sym, dcl);
		} else {
			yy_error_sym("unexpected", sym);
		}
	} while (YY_IN_SET(sym, (YY_CONST,YY___CONST,YY___CONST__,YY_RESTRICT,YY___RESTRICT,YY___RESTRICT__,YY_VOLATILE,YY___VOLATILE,YY___VOLATILE__,YY__ATOMIC,YY___ATTRIBUTE,YY___ATTRIBUTE__,YY___DECLSPEC), "\000\000\340\177\000\000\000\007\000\000\000\000\000"));
	return sym;
}