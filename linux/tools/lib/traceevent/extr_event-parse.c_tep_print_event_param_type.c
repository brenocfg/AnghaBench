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
struct print_event_type {scalar_t__ type; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ EVENT_TYPE_INT ; 
 scalar_t__ EVENT_TYPE_STRING ; 
 scalar_t__ EVENT_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tep_print_event_param_type(char *format,
				      struct print_event_type *type)
{
	char *str = format + 1;
	int i = 1;

	type->type = EVENT_TYPE_UNKNOWN;
	while (*str) {
		switch (*str) {
		case 'd':
		case 'u':
		case 'i':
		case 'x':
		case 'X':
		case 'o':
			type->type = EVENT_TYPE_INT;
			break;
		case 's':
			type->type = EVENT_TYPE_STRING;
			break;
		}
		str++;
		i++;
		if (type->type != EVENT_TYPE_UNKNOWN)
			break;
	}
	memset(type->format, 0, 32);
	memcpy(type->format, format, i < 32 ? i : 31);
	return i;
}