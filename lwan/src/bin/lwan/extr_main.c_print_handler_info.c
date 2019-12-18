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
struct lwan_handler_info {char* name; } ;
typedef  int /*<<< orphan*/  lwan_handler ;

/* Variables and functions */
 struct lwan_handler_info* __start_lwan_handler ; 
 struct lwan_handler_info const* __stop_lwan_handler ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_handler_info(void)
{
    extern const struct lwan_handler_info SECTION_START(lwan_handler);
    extern const struct lwan_handler_info SECTION_END(lwan_handler);
    const struct lwan_handler_info *handler;

    printf("Available handlers:\n");
    for (handler = __start_lwan_handler; handler < __stop_lwan_handler; handler++) {
        printf(" * %s\n", handler->name);
    }
}