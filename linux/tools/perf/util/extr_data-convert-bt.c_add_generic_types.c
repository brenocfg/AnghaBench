#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int sample_type; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct TYPE_6__ {int /*<<< orphan*/  u64_hex; int /*<<< orphan*/  u32; int /*<<< orphan*/  u64; int /*<<< orphan*/  s32; } ;
struct ctf_writer {TYPE_3__ data; } ;
struct bt_ctf_event_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_FIELD (struct bt_ctf_event_class*,int /*<<< orphan*/ ,char*) ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_DATA_SRC ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_IDENTIFIER ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TRANSACTION ; 
 int PERF_SAMPLE_WEIGHT ; 
 int /*<<< orphan*/  bt_ctf_field_type_sequence_create (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int add_generic_types(struct ctf_writer *cw, struct evsel *evsel,
			     struct bt_ctf_event_class *event_class)
{
	u64 type = evsel->core.attr.sample_type;

	/*
	 * missing:
	 *   PERF_SAMPLE_TIME         - not needed as we have it in
	 *                              ctf event header
	 *   PERF_SAMPLE_READ         - TODO
	 *   PERF_SAMPLE_CALLCHAIN    - TODO
	 *   PERF_SAMPLE_RAW          - tracepoint fields and BPF output
	 *                              are handled separately
	 *   PERF_SAMPLE_BRANCH_STACK - TODO
	 *   PERF_SAMPLE_REGS_USER    - TODO
	 *   PERF_SAMPLE_STACK_USER   - TODO
	 */

#define ADD_FIELD(cl, t, n)						\
	do {								\
		pr2("  field '%s'\n", n);				\
		if (bt_ctf_event_class_add_field(cl, t, n)) {		\
			pr_err("Failed to add field '%s';\n", n);	\
			return -1;					\
		}							\
	} while (0)

	if (type & PERF_SAMPLE_IP)
		ADD_FIELD(event_class, cw->data.u64_hex, "perf_ip");

	if (type & PERF_SAMPLE_TID) {
		ADD_FIELD(event_class, cw->data.s32, "perf_tid");
		ADD_FIELD(event_class, cw->data.s32, "perf_pid");
	}

	if ((type & PERF_SAMPLE_ID) ||
	    (type & PERF_SAMPLE_IDENTIFIER))
		ADD_FIELD(event_class, cw->data.u64, "perf_id");

	if (type & PERF_SAMPLE_STREAM_ID)
		ADD_FIELD(event_class, cw->data.u64, "perf_stream_id");

	if (type & PERF_SAMPLE_PERIOD)
		ADD_FIELD(event_class, cw->data.u64, "perf_period");

	if (type & PERF_SAMPLE_WEIGHT)
		ADD_FIELD(event_class, cw->data.u64, "perf_weight");

	if (type & PERF_SAMPLE_DATA_SRC)
		ADD_FIELD(event_class, cw->data.u64, "perf_data_src");

	if (type & PERF_SAMPLE_TRANSACTION)
		ADD_FIELD(event_class, cw->data.u64, "perf_transaction");

	if (type & PERF_SAMPLE_CALLCHAIN) {
		ADD_FIELD(event_class, cw->data.u32, "perf_callchain_size");
		ADD_FIELD(event_class,
			bt_ctf_field_type_sequence_create(
				cw->data.u64_hex, "perf_callchain_size"),
			"perf_callchain");
	}

#undef ADD_FIELD
	return 0;
}