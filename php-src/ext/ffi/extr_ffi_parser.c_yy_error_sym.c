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

/* Variables and functions */
 int /*<<< orphan*/ * sym_name ; 
 int /*<<< orphan*/  yy_line ; 
 int /*<<< orphan*/  zend_ffi_parser_error (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yy_error_sym(const char *msg, int sym) {
	zend_ffi_parser_error("%s '%s' at line %d", msg, sym_name[sym], yy_line);
}