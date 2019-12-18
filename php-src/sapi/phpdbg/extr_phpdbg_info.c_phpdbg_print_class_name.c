#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ce_flags; int /*<<< orphan*/  function_table; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_INTERFACE ; 
 int /*<<< orphan*/  ZEND_USER_CLASS ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phpdbg_writeln (char*,char*,char*,char const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void phpdbg_print_class_name(zend_class_entry *ce) /* {{{ */
{
	const char *visibility = ce->type == ZEND_USER_CLASS ? "User" : "Internal";
	const char *type = (ce->ce_flags & ZEND_ACC_INTERFACE) ? "Interface" : (ce->ce_flags & ZEND_ACC_ABSTRACT) ? "Abstract Class" : "Class";

	phpdbg_writeln("class", "type=\"%s\" flags=\"%s\" name=\"%.*s\" methodcount=\"%d\"", "%s %s %.*s (%d)", visibility, type, (int) ZSTR_LEN(ce->name), ZSTR_VAL(ce->name), zend_hash_num_elements(&ce->function_table));
}