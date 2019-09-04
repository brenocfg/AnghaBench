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
struct format_field {struct format_field* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_warning (char*,char const*,char const*) ; 
 struct format_field** malloc (int) ; 

__attribute__((used)) static struct format_field **
get_event_fields(const char *type, const char *name,
		 int count, struct format_field *list)
{
	struct format_field **fields;
	struct format_field *field;
	int i = 0;

	fields = malloc(sizeof(*fields) * (count + 1));
	if (!fields)
		return NULL;

	for (field = list; field; field = field->next) {
		fields[i++] = field;
		if (i == count + 1) {
			do_warning("event %s has more %s fields than specified",
				name, type);
			i--;
			break;
		}
	}

	if (i != count)
		do_warning("event %s has less %s fields than specified",
			name, type);

	fields[i] = NULL;

	return fields;
}