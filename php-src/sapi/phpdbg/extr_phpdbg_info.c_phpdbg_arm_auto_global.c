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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ (* auto_global_callback ) (int /*<<< orphan*/ ) ;scalar_t__ armed; } ;
typedef  TYPE_1__ zend_auto_global ;

/* Variables and functions */
 int PHPDBG_G (int /*<<< orphan*/ ) ; 
 int PHPDBG_IN_SIGNAL_HANDLER ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  phpdbg_notice (char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phpdbg_arm_auto_global(zval *ptrzv) {
	zend_auto_global *auto_global = Z_PTR_P(ptrzv);

	if (auto_global->armed) {
		if (PHPDBG_G(flags) & PHPDBG_IN_SIGNAL_HANDLER) {
			phpdbg_notice("variableinfo", "unreachable=\"%.*s\"", "Cannot show information about superglobal variable %.*s", (int) ZSTR_LEN(auto_global->name), ZSTR_VAL(auto_global->name));
		} else {
			auto_global->armed = auto_global->auto_global_callback(auto_global->name);
		}
	}

	return 0;
}