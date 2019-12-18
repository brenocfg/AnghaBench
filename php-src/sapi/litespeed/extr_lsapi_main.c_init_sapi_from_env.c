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
struct TYPE_3__ {char* php_ini_path_override; } ;
typedef  TYPE_1__ sapi_module_struct ;

/* Variables and functions */
 char* getenv (char*) ; 

__attribute__((used)) static void init_sapi_from_env(sapi_module_struct *sapi_module)
{
    char *p;
    p = getenv("LSPHPRC");
    if (p)
        sapi_module->php_ini_path_override = p;
}