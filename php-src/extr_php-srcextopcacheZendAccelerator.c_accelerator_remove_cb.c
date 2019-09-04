#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * op_array_handler; int /*<<< orphan*/ * deactivate; int /*<<< orphan*/ * activate; int /*<<< orphan*/ * startup; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_extension ;

/* Variables and functions */
 int /*<<< orphan*/  ACCELERATOR_PRODUCT_NAME ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int accelerator_remove_cb(zend_extension *element1, zend_extension *element2)
{
	(void)element2; /* keep the compiler happy */

	if (!strcmp(element1->name, ACCELERATOR_PRODUCT_NAME )) {
		element1->startup = NULL;
#if 0
		/* We have to call shutdown callback it to free TS resources */
		element1->shutdown = NULL;
#endif
		element1->activate = NULL;
		element1->deactivate = NULL;
		element1->op_array_handler = NULL;

#ifdef __DEBUG_MESSAGES__
        fprintf(stderr, ACCELERATOR_PRODUCT_NAME " is disabled: %s\n", (zps_failure_reason ? zps_failure_reason : "unknown error"));
        fflush(stderr);
#endif
	}

	return 0;
}