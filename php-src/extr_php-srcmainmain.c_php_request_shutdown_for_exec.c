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
 int /*<<< orphan*/  shutdown_memory_manager (int,int) ; 
 int /*<<< orphan*/  zend_interned_strings_deactivate () ; 

void php_request_shutdown_for_exec(void *dummy)
{

	/* used to close fd's in the 3..255 range here, but it's problematic
	 */
	zend_interned_strings_deactivate();
	shutdown_memory_manager(1, 1);
}