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
struct TYPE_4__ {int /*<<< orphan*/  executable_location; } ;
typedef  TYPE_1__ sapi_module_struct ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  argv0 ; 
 scalar_t__ php_module_startup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_lsapi_startup(sapi_module_struct *sapi_module)
{
    if (php_module_startup(sapi_module, NULL, 0)==FAILURE) {
        return FAILURE;
    }
    argv0 = sapi_module->executable_location;
    return SUCCESS;
}