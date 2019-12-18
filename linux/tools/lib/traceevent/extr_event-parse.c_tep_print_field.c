#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_seq {int dummy; } ;
struct tep_handle {int dummy; } ;
struct tep_format_field {int flags; unsigned int offset; unsigned int size; TYPE_1__* event; } ;
struct TYPE_2__ {struct tep_handle* tep; } ;

/* Variables and functions */
 int TEP_FIELD_IS_ARRAY ; 
 int TEP_FIELD_IS_DYNAMIC ; 
 int TEP_FIELD_IS_LONG ; 
 int TEP_FIELD_IS_POINTER ; 
 int TEP_FIELD_IS_SIGNED ; 
 int TEP_FIELD_IS_STRING ; 
 scalar_t__ is_printable_array (void*,unsigned int) ; 
 unsigned long long tep_read_number (struct tep_handle*,void*,unsigned int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

void tep_print_field(struct trace_seq *s, void *data,
		     struct tep_format_field *field)
{
	unsigned long long val;
	unsigned int offset, len, i;
	struct tep_handle *tep = field->event->tep;

	if (field->flags & TEP_FIELD_IS_ARRAY) {
		offset = field->offset;
		len = field->size;
		if (field->flags & TEP_FIELD_IS_DYNAMIC) {
			val = tep_read_number(tep, data + offset, len);
			offset = val;
			len = offset >> 16;
			offset &= 0xffff;
		}
		if (field->flags & TEP_FIELD_IS_STRING &&
		    is_printable_array(data + offset, len)) {
			trace_seq_printf(s, "%s", (char *)data + offset);
		} else {
			trace_seq_puts(s, "ARRAY[");
			for (i = 0; i < len; i++) {
				if (i)
					trace_seq_puts(s, ", ");
				trace_seq_printf(s, "%02x",
						 *((unsigned char *)data + offset + i));
			}
			trace_seq_putc(s, ']');
			field->flags &= ~TEP_FIELD_IS_STRING;
		}
	} else {
		val = tep_read_number(tep, data + field->offset,
				      field->size);
		if (field->flags & TEP_FIELD_IS_POINTER) {
			trace_seq_printf(s, "0x%llx", val);
		} else if (field->flags & TEP_FIELD_IS_SIGNED) {
			switch (field->size) {
			case 4:
				/*
				 * If field is long then print it in hex.
				 * A long usually stores pointers.
				 */
				if (field->flags & TEP_FIELD_IS_LONG)
					trace_seq_printf(s, "0x%x", (int)val);
				else
					trace_seq_printf(s, "%d", (int)val);
				break;
			case 2:
				trace_seq_printf(s, "%2d", (short)val);
				break;
			case 1:
				trace_seq_printf(s, "%1d", (char)val);
				break;
			default:
				trace_seq_printf(s, "%lld", val);
			}
		} else {
			if (field->flags & TEP_FIELD_IS_LONG)
				trace_seq_printf(s, "0x%llx", val);
			else
				trace_seq_printf(s, "%llu", val);
		}
	}
}