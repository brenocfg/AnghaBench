#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tep_record {char* data; } ;
struct tep_handle {int dummy; } ;
struct TYPE_3__ {char* buffer; TYPE_2__* field; } ;
struct tep_filter_arg {TYPE_1__ str; } ;
struct tep_event {struct tep_handle* tep; } ;
struct TYPE_4__ {int flags; int offset; unsigned int size; struct tep_event* event; } ;

/* Variables and functions */
 int TEP_FIELD_IS_DYNAMIC ; 
 int TEP_FIELD_IS_LONG ; 
 int TEP_FIELD_IS_POINTER ; 
 int TEP_FIELD_IS_STRING ; 
 unsigned long long get_value (struct tep_event*,TYPE_2__*,struct tep_record*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 char* tep_find_function (struct tep_handle*,unsigned long long) ; 

__attribute__((used)) static const char *get_field_str(struct tep_filter_arg *arg, struct tep_record *record)
{
	struct tep_event *event;
	struct tep_handle *tep;
	unsigned long long addr;
	const char *val = NULL;
	unsigned int size;
	char hex[64];

	/* If the field is not a string convert it */
	if (arg->str.field->flags & TEP_FIELD_IS_STRING) {
		val = record->data + arg->str.field->offset;
		size = arg->str.field->size;

		if (arg->str.field->flags & TEP_FIELD_IS_DYNAMIC) {
			addr = *(unsigned int *)val;
			val = record->data + (addr & 0xffff);
			size = addr >> 16;
		}

		/*
		 * We need to copy the data since we can't be sure the field
		 * is null terminated.
		 */
		if (*(val + size - 1)) {
			/* copy it */
			memcpy(arg->str.buffer, val, arg->str.field->size);
			/* the buffer is already NULL terminated */
			val = arg->str.buffer;
		}

	} else {
		event = arg->str.field->event;
		tep = event->tep;
		addr = get_value(event, arg->str.field, record);

		if (arg->str.field->flags & (TEP_FIELD_IS_POINTER | TEP_FIELD_IS_LONG))
			/* convert to a kernel symbol */
			val = tep_find_function(tep, addr);

		if (val == NULL) {
			/* just use the hex of the string name */
			snprintf(hex, 64, "0x%llx", addr);
			val = hex;
		}
	}

	return val;
}