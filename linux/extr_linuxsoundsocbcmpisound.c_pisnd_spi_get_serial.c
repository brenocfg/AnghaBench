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
 char const* g_serial_num ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *pisnd_spi_get_serial(void)
{
	if (strlen(g_serial_num))
		return g_serial_num;

	return "";
}