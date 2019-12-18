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
struct lwan_module_info {char* name; } ;
typedef  int /*<<< orphan*/  lwan_module ;

/* Variables and functions */
 struct lwan_module_info* __start_lwan_module ; 
 struct lwan_module_info const* __stop_lwan_module ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_module_info(void)
{
    extern const struct lwan_module_info SECTION_START(lwan_module);
    extern const struct lwan_module_info SECTION_END(lwan_module);
    const struct lwan_module_info *module;

    printf("Available modules:\n");
    for (module = __start_lwan_module; module < __stop_lwan_module; module++) {
        printf(" * %s\n", module->name);
    }
}