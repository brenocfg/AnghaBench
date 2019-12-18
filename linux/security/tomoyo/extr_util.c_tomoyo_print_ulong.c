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
typedef  int u8 ;

/* Variables and functions */
 int const TOMOYO_VALUE_TYPE_DECIMAL ; 
 int const TOMOYO_VALUE_TYPE_HEXADECIMAL ; 
 int const TOMOYO_VALUE_TYPE_OCTAL ; 
 int /*<<< orphan*/  snprintf (char*,int const,char*,int const) ; 

void tomoyo_print_ulong(char *buffer, const int buffer_len,
			const unsigned long value, const u8 type)
{
	if (type == TOMOYO_VALUE_TYPE_DECIMAL)
		snprintf(buffer, buffer_len, "%lu", value);
	else if (type == TOMOYO_VALUE_TYPE_OCTAL)
		snprintf(buffer, buffer_len, "0%lo", value);
	else if (type == TOMOYO_VALUE_TYPE_HEXADECIMAL)
		snprintf(buffer, buffer_len, "0x%lX", value);
	else
		snprintf(buffer, buffer_len, "type(%u)", type);
}