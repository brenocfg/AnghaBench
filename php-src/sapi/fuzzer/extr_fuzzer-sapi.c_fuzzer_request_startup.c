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
typedef  int /*<<< orphan*/  SIGG ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_module_shutdown () ; 
 scalar_t__ php_request_startup () ; 

int fuzzer_request_startup()
{
	if (php_request_startup() == FAILURE) {
		php_module_shutdown();
		return FAILURE;
	}

#ifdef ZEND_SIGNALS
	/* Some signal handlers will be overriden,
	 * don't complain about them during shutdown. */
	SIGG(check) = 0;
#endif

	return SUCCESS;
}