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
struct tep_handle {int dummy; } ;
struct tep_format_field {int offset; int size; } ;
struct tep_event {int dummy; } ;
struct scripting_context {scalar_t__ event_data; struct tep_handle* pevent; } ;

/* Variables and functions */
 struct tep_format_field* tep_find_common_field (struct tep_event*,char const*) ; 
 struct tep_event* tep_get_first_event (struct tep_handle*) ; 
 int tep_read_number (struct tep_handle*,scalar_t__,int) ; 

__attribute__((used)) static int get_common_field(struct scripting_context *context,
			    int *offset, int *size, const char *type)
{
	struct tep_handle *pevent = context->pevent;
	struct tep_event *event;
	struct tep_format_field *field;

	if (!*size) {

		event = tep_get_first_event(pevent);
		if (!event)
			return 0;

		field = tep_find_common_field(event, type);
		if (!field)
			return 0;
		*offset = field->offset;
		*size = field->size;
	}

	return tep_read_number(pevent, context->event_data + *offset, *size);
}