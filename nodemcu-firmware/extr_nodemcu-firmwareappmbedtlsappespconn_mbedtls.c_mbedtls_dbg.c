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
 int /*<<< orphan*/  os_printf (char*,int,int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  system_get_free_heap_size () ; 

__attribute__((used)) static void
mbedtls_dbg(void *p, int level, const char *file, int line, const char *str)
{
	os_printf("TLS<%d> (heap=%d): %s:%d %s", level, system_get_free_heap_size(), file, line, str);
}