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
struct trace_entry {int type; } ;

/* Variables and functions */
 int BASE_PREFIX ; 
 int PREFIX_DELTA ; 
#define  TRACE_TYPE_COUNTER 132 
#define  TRACE_TYPE_INDENT 131 
#define  TRACE_TYPE_OUTDENT 130 
#define  TRACE_TYPE_REG 129 
#define  TRACE_TYPE_STRING 128 
 int /*<<< orphan*/  printf (char*,struct trace_entry*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  trace_print_counter (struct trace_entry*) ; 
 int /*<<< orphan*/  trace_print_header (int,int) ; 
 int /*<<< orphan*/  trace_print_reg (struct trace_entry*) ; 
 int /*<<< orphan*/  trace_print_string (struct trace_entry*) ; 

__attribute__((used)) static void trace_print_entry(struct trace_entry *e, int seq, int *prefix)
{
	switch (e->type) {
	case TRACE_TYPE_REG:
		trace_print_header(seq, *prefix);
		trace_print_reg(e);
		break;
	case TRACE_TYPE_COUNTER:
		trace_print_header(seq, *prefix);
		trace_print_counter(e);
		break;
	case TRACE_TYPE_STRING:
		trace_print_header(seq, *prefix);
		trace_print_string(e);
		break;
	case TRACE_TYPE_INDENT:
		trace_print_header(seq, *prefix);
		puts("{");
		*prefix += PREFIX_DELTA;
		break;
	case TRACE_TYPE_OUTDENT:
		*prefix -= PREFIX_DELTA;
		if (*prefix < BASE_PREFIX)
			*prefix = BASE_PREFIX;
		trace_print_header(seq, *prefix);
		puts("}");
		break;
	default:
		trace_print_header(seq, *prefix);
		printf("entry @ %p type %d\n", e, e->type);
		break;
	}
}