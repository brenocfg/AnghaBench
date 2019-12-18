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
typedef  int /*<<< orphan*/  CONF_IMODULE ;

/* Variables and functions */
 int /*<<< orphan*/ * initialized_modules ; 
 int /*<<< orphan*/  module_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_CONF_IMODULE_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_CONF_IMODULE_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_CONF_IMODULE_pop (int /*<<< orphan*/ *) ; 

void CONF_modules_finish(void)
{
    CONF_IMODULE *imod;
    while (sk_CONF_IMODULE_num(initialized_modules) > 0) {
        imod = sk_CONF_IMODULE_pop(initialized_modules);
        module_finish(imod);
    }
    sk_CONF_IMODULE_free(initialized_modules);
    initialized_modules = NULL;
}