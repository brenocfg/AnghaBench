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
typedef  int /*<<< orphan*/  timelib_format_specifier_code ;
struct TYPE_3__ {char specifier; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ timelib_format_specifier ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_FORMAT_LITERAL ; 

__attribute__((used)) static timelib_format_specifier_code timelib_lookup_format(char input, const timelib_format_specifier* format_map)
{
	while (format_map && format_map->specifier != '\0') {
		if (format_map->specifier == input) {
			return format_map->code;
		}
		format_map++;
	}
	return TIMELIB_FORMAT_LITERAL;
}