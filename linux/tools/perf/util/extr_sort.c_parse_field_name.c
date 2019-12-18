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
 char* strchr (char*,char) ; 

__attribute__((used)) static int parse_field_name(char *str, char **event, char **field, char **opt)
{
	char *event_name, *field_name, *opt_name;

	event_name = str;
	field_name = strchr(str, '.');

	if (field_name) {
		*field_name++ = '\0';
	} else {
		event_name = NULL;
		field_name = str;
	}

	opt_name = strchr(field_name, '/');
	if (opt_name)
		*opt_name++ = '\0';

	*event = event_name;
	*field = field_name;
	*opt   = opt_name;

	return 0;
}