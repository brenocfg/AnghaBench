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
struct tep_format_field {char* name; } ;
struct hpp_dynamic_entry {size_t dynamic_len; scalar_t__ raw_trace; struct tep_format_field* field; } ;
struct hist_entry {char* trace_output; } ;

/* Variables and functions */
 char* get_trace_output (struct hist_entry*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 

__attribute__((used)) static void update_dynamic_len(struct hpp_dynamic_entry *hde,
			       struct hist_entry *he)
{
	char *str, *pos;
	struct tep_format_field *field = hde->field;
	size_t namelen;
	bool last = false;

	if (hde->raw_trace)
		return;

	/* parse pretty print result and update max length */
	if (!he->trace_output)
		he->trace_output = get_trace_output(he);

	namelen = strlen(field->name);
	str = he->trace_output;

	while (str) {
		pos = strchr(str, ' ');
		if (pos == NULL) {
			last = true;
			pos = str + strlen(str);
		}

		if (!strncmp(str, field->name, namelen)) {
			size_t len;

			str += namelen + 1;
			len = pos - str;

			if (len > hde->dynamic_len)
				hde->dynamic_len = len;
			break;
		}

		if (last)
			str = NULL;
		else
			str = pos + 1;
	}
}