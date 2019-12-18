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
struct tep_record {unsigned long long cpu; int /*<<< orphan*/  data; } ;
struct tep_format_field {int flags; int size; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 int TEP_FIELD_IS_SIGNED ; 
 struct tep_format_field comm ; 
 struct tep_format_field cpu ; 
 char* get_comm (struct tep_event*,struct tep_record*) ; 
 int /*<<< orphan*/  tep_read_number_field (struct tep_format_field*,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static unsigned long long
get_value(struct tep_event *event,
	  struct tep_format_field *field, struct tep_record *record)
{
	unsigned long long val;

	/* Handle our dummy "comm" field */
	if (field == &comm) {
		const char *name;

		name = get_comm(event, record);
		return (unsigned long)name;
	}

	/* Handle our dummy "cpu" field */
	if (field == &cpu)
		return record->cpu;

	tep_read_number_field(field, record->data, &val);

	if (!(field->flags & TEP_FIELD_IS_SIGNED))
		return val;

	switch (field->size) {
	case 1:
		return (char)val;
	case 2:
		return (short)val;
	case 4:
		return (int)val;
	case 8:
		return (long long)val;
	}
	return val;
}