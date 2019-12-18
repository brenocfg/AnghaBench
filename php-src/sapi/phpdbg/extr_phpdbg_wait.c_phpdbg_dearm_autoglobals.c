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
struct TYPE_3__ {scalar_t__ armed; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_auto_global ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 
 int ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int phpdbg_dearm_autoglobals(zend_auto_global *auto_global) {
	if (ZSTR_LEN(auto_global->name) != sizeof("GLOBALS") - 1 || memcmp(ZSTR_VAL(auto_global->name), "GLOBALS", sizeof("GLOBALS") - 1)) {
		auto_global->armed = 0;
	}

	return ZEND_HASH_APPLY_KEEP;
}