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
 int /*<<< orphan*/  fdt_set_size_dt_strings (void*,scalar_t__) ; 
 scalar_t__ fdt_size_dt_strings (void*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void fdt_del_last_string_(void *fdt, const char *s)
{
	int newlen = strlen(s) + 1;

	fdt_set_size_dt_strings(fdt, fdt_size_dt_strings(fdt) - newlen);
}