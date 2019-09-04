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
 int /*<<< orphan*/  php_info_print_table_row (int,char const* const,char const* const,char const* const) ; 

__attribute__((used)) static void __enumerate_providers_fn (const char * const name,
                        const char * const desc,
                        const char * const file,
                        void * ud) /* {{{ */
{
	php_info_print_table_row(3, name, desc, file);
}