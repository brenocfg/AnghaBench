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
 int parse_abstract_declarator (int,int /*<<< orphan*/ *) ; 
 int parse_specifier_qualifier_list (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_type_name(int sym, zend_ffi_dcl *dcl) {
	sym = parse_specifier_qualifier_list(sym, dcl);
	sym = parse_abstract_declarator(sym, dcl);
	return sym;
}