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
struct trace_seq {int len; char* buffer; } ;
struct tep_record {scalar_t__ data; } ;
struct tep_format_field {TYPE_1__* event; int /*<<< orphan*/  size; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 int /*<<< orphan*/  tep_register_comm (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  trace_seq_terminate (struct trace_seq*) ; 

__attribute__((used)) static void write_and_save_comm(struct tep_format_field *field,
				struct tep_record *record,
				struct trace_seq *s, int pid)
{
	const char *comm;
	int len;

	comm = (char *)(record->data + field->offset);
	len = s->len;
	trace_seq_printf(s, "%.*s",
			 field->size, comm);

	/* make sure the comm has a \0 at the end. */
	trace_seq_terminate(s);
	comm = &s->buffer[len];

	/* Help out the comm to ids. This will handle dups */
	tep_register_comm(field->event->tep, comm, pid);
}