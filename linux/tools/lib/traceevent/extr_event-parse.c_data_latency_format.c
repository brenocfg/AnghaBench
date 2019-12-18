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
struct trace_seq {scalar_t__ state; int /*<<< orphan*/  buffer; } ;
struct tep_record {void* data; } ;
struct tep_handle {int dummy; } ;

/* Variables and functions */
 unsigned int TRACE_FLAG_HARDIRQ ; 
 unsigned int TRACE_FLAG_IRQS_NOSUPPORT ; 
 unsigned int TRACE_FLAG_IRQS_OFF ; 
 unsigned int TRACE_FLAG_NEED_RESCHED ; 
 unsigned int TRACE_FLAG_SOFTIRQ ; 
 scalar_t__ TRACE_SEQ__MEM_ALLOC_FAILED ; 
 unsigned int parse_common_flags (struct tep_handle*,void*) ; 
 int parse_common_lock_depth (struct tep_handle*,void*) ; 
 int parse_common_migrate_disable (struct tep_handle*,void*) ; 
 unsigned int parse_common_pc (struct tep_handle*,void*) ; 
 int /*<<< orphan*/  trace_seq_destroy (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_terminate (struct trace_seq*) ; 

__attribute__((used)) static void data_latency_format(struct tep_handle *tep, struct trace_seq *s,
				char *format, struct tep_record *record)
{
	static int check_lock_depth = 1;
	static int check_migrate_disable = 1;
	static int lock_depth_exists;
	static int migrate_disable_exists;
	unsigned int lat_flags;
	struct trace_seq sq;
	unsigned int pc;
	int lock_depth = 0;
	int migrate_disable = 0;
	int hardirq;
	int softirq;
	void *data = record->data;

	trace_seq_init(&sq);
	lat_flags = parse_common_flags(tep, data);
	pc = parse_common_pc(tep, data);
	/* lock_depth may not always exist */
	if (lock_depth_exists)
		lock_depth = parse_common_lock_depth(tep, data);
	else if (check_lock_depth) {
		lock_depth = parse_common_lock_depth(tep, data);
		if (lock_depth < 0)
			check_lock_depth = 0;
		else
			lock_depth_exists = 1;
	}

	/* migrate_disable may not always exist */
	if (migrate_disable_exists)
		migrate_disable = parse_common_migrate_disable(tep, data);
	else if (check_migrate_disable) {
		migrate_disable = parse_common_migrate_disable(tep, data);
		if (migrate_disable < 0)
			check_migrate_disable = 0;
		else
			migrate_disable_exists = 1;
	}

	hardirq = lat_flags & TRACE_FLAG_HARDIRQ;
	softirq = lat_flags & TRACE_FLAG_SOFTIRQ;

	trace_seq_printf(&sq, "%c%c%c",
	       (lat_flags & TRACE_FLAG_IRQS_OFF) ? 'd' :
	       (lat_flags & TRACE_FLAG_IRQS_NOSUPPORT) ?
	       'X' : '.',
	       (lat_flags & TRACE_FLAG_NEED_RESCHED) ?
	       'N' : '.',
	       (hardirq && softirq) ? 'H' :
	       hardirq ? 'h' : softirq ? 's' : '.');

	if (pc)
		trace_seq_printf(&sq, "%x", pc);
	else
		trace_seq_printf(&sq, ".");

	if (migrate_disable_exists) {
		if (migrate_disable < 0)
			trace_seq_printf(&sq, ".");
		else
			trace_seq_printf(&sq, "%d", migrate_disable);
	}

	if (lock_depth_exists) {
		if (lock_depth < 0)
			trace_seq_printf(&sq, ".");
		else
			trace_seq_printf(&sq, "%d", lock_depth);
	}

	if (sq.state == TRACE_SEQ__MEM_ALLOC_FAILED) {
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
		return;
	}

	trace_seq_terminate(&sq);
	trace_seq_puts(s, sq.buffer);
	trace_seq_destroy(&sq);
	trace_seq_terminate(s);
}