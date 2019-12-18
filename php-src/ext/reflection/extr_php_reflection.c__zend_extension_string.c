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
struct TYPE_3__ {int /*<<< orphan*/  URL; int /*<<< orphan*/  author; int /*<<< orphan*/  copyright; int /*<<< orphan*/  version; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_extension ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  smart_str_appends (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void _zend_extension_string(smart_str *str, zend_extension *extension, char *indent) /* {{{ */
{
	smart_str_append_printf(str, "%sZend Extension [ %s ", indent, extension->name);

	if (extension->version) {
		smart_str_append_printf(str, "%s ", extension->version);
	}
	if (extension->copyright) {
		smart_str_append_printf(str, "%s ", extension->copyright);
	}
	if (extension->author) {
		smart_str_append_printf(str, "by %s ", extension->author);
	}
	if (extension->URL) {
		smart_str_append_printf(str, "<%s> ", extension->URL);
	}

	smart_str_appends(str, "]\n");
}