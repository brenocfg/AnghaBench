#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_7__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_INI_STAGE_RUNTIME ; 
 int /*<<< orphan*/  PHP_INI_USER ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_str_append (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_1__*) ; 
 int zend_alter_ini_entry_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_session_start_set_ini(zend_string *varname, zend_string *new_value) {
	int ret;
	smart_str buf ={0};
	smart_str_appends(&buf, "session");
	smart_str_appendc(&buf, '.');
	smart_str_append(&buf, varname);
	smart_str_0(&buf);
	ret = zend_alter_ini_entry_ex(buf.s, new_value, PHP_INI_USER, PHP_INI_STAGE_RUNTIME, 0);
	smart_str_free(&buf);
	return ret;
}