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
struct trace_event_file {unsigned long flags; int /*<<< orphan*/  sm_ref; struct trace_array* tr; struct trace_event_call* event_call; } ;
struct trace_event_call {TYPE_1__* class; } ;
struct trace_array {int trace_flags; } ;
struct TYPE_2__ {int (* reg ) (struct trace_event_call*,int /*<<< orphan*/ ,struct trace_event_file*) ;} ;

/* Variables and functions */
 int EVENT_FILE_FL_ENABLED ; 
 int /*<<< orphan*/  EVENT_FILE_FL_ENABLED_BIT ; 
 int EVENT_FILE_FL_RECORDED_CMD ; 
 int /*<<< orphan*/  EVENT_FILE_FL_RECORDED_CMD_BIT ; 
 int EVENT_FILE_FL_RECORDED_TGID ; 
 int /*<<< orphan*/  EVENT_FILE_FL_RECORDED_TGID_BIT ; 
 unsigned long EVENT_FILE_FL_SOFT_DISABLED ; 
 int /*<<< orphan*/  EVENT_FILE_FL_SOFT_DISABLED_BIT ; 
 int EVENT_FILE_FL_SOFT_MODE ; 
 int /*<<< orphan*/  EVENT_FILE_FL_SOFT_MODE_BIT ; 
 int /*<<< orphan*/  EVENT_FILE_FL_WAS_ENABLED_BIT ; 
 int TRACE_ITER_RECORD_CMD ; 
 int TRACE_ITER_RECORD_TGID ; 
 int /*<<< orphan*/  TRACE_REG_REGISTER ; 
 int /*<<< orphan*/  TRACE_REG_UNREGISTER ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int stub1 (struct trace_event_call*,int /*<<< orphan*/ ,struct trace_event_file*) ; 
 int stub2 (struct trace_event_call*,int /*<<< orphan*/ ,struct trace_event_file*) ; 
 int /*<<< orphan*/  trace_buffered_event_disable () ; 
 int /*<<< orphan*/  trace_buffered_event_enable () ; 
 int /*<<< orphan*/  trace_event_name (struct trace_event_call*) ; 
 int /*<<< orphan*/  tracing_start_cmdline_record () ; 
 int /*<<< orphan*/  tracing_start_tgid_record () ; 
 int /*<<< orphan*/  tracing_stop_cmdline_record () ; 
 int /*<<< orphan*/  tracing_stop_tgid_record () ; 

__attribute__((used)) static int __ftrace_event_enable_disable(struct trace_event_file *file,
					 int enable, int soft_disable)
{
	struct trace_event_call *call = file->event_call;
	struct trace_array *tr = file->tr;
	unsigned long file_flags = file->flags;
	int ret = 0;
	int disable;

	switch (enable) {
	case 0:
		/*
		 * When soft_disable is set and enable is cleared, the sm_ref
		 * reference counter is decremented. If it reaches 0, we want
		 * to clear the SOFT_DISABLED flag but leave the event in the
		 * state that it was. That is, if the event was enabled and
		 * SOFT_DISABLED isn't set, then do nothing. But if SOFT_DISABLED
		 * is set we do not want the event to be enabled before we
		 * clear the bit.
		 *
		 * When soft_disable is not set but the SOFT_MODE flag is,
		 * we do nothing. Do not disable the tracepoint, otherwise
		 * "soft enable"s (clearing the SOFT_DISABLED bit) wont work.
		 */
		if (soft_disable) {
			if (atomic_dec_return(&file->sm_ref) > 0)
				break;
			disable = file->flags & EVENT_FILE_FL_SOFT_DISABLED;
			clear_bit(EVENT_FILE_FL_SOFT_MODE_BIT, &file->flags);
		} else
			disable = !(file->flags & EVENT_FILE_FL_SOFT_MODE);

		if (disable && (file->flags & EVENT_FILE_FL_ENABLED)) {
			clear_bit(EVENT_FILE_FL_ENABLED_BIT, &file->flags);
			if (file->flags & EVENT_FILE_FL_RECORDED_CMD) {
				tracing_stop_cmdline_record();
				clear_bit(EVENT_FILE_FL_RECORDED_CMD_BIT, &file->flags);
			}

			if (file->flags & EVENT_FILE_FL_RECORDED_TGID) {
				tracing_stop_tgid_record();
				clear_bit(EVENT_FILE_FL_RECORDED_TGID_BIT, &file->flags);
			}

			call->class->reg(call, TRACE_REG_UNREGISTER, file);
		}
		/* If in SOFT_MODE, just set the SOFT_DISABLE_BIT, else clear it */
		if (file->flags & EVENT_FILE_FL_SOFT_MODE)
			set_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &file->flags);
		else
			clear_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &file->flags);
		break;
	case 1:
		/*
		 * When soft_disable is set and enable is set, we want to
		 * register the tracepoint for the event, but leave the event
		 * as is. That means, if the event was already enabled, we do
		 * nothing (but set SOFT_MODE). If the event is disabled, we
		 * set SOFT_DISABLED before enabling the event tracepoint, so
		 * it still seems to be disabled.
		 */
		if (!soft_disable)
			clear_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &file->flags);
		else {
			if (atomic_inc_return(&file->sm_ref) > 1)
				break;
			set_bit(EVENT_FILE_FL_SOFT_MODE_BIT, &file->flags);
		}

		if (!(file->flags & EVENT_FILE_FL_ENABLED)) {
			bool cmd = false, tgid = false;

			/* Keep the event disabled, when going to SOFT_MODE. */
			if (soft_disable)
				set_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &file->flags);

			if (tr->trace_flags & TRACE_ITER_RECORD_CMD) {
				cmd = true;
				tracing_start_cmdline_record();
				set_bit(EVENT_FILE_FL_RECORDED_CMD_BIT, &file->flags);
			}

			if (tr->trace_flags & TRACE_ITER_RECORD_TGID) {
				tgid = true;
				tracing_start_tgid_record();
				set_bit(EVENT_FILE_FL_RECORDED_TGID_BIT, &file->flags);
			}

			ret = call->class->reg(call, TRACE_REG_REGISTER, file);
			if (ret) {
				if (cmd)
					tracing_stop_cmdline_record();
				if (tgid)
					tracing_stop_tgid_record();
				pr_info("event trace: Could not enable event "
					"%s\n", trace_event_name(call));
				break;
			}
			set_bit(EVENT_FILE_FL_ENABLED_BIT, &file->flags);

			/* WAS_ENABLED gets set but never cleared. */
			set_bit(EVENT_FILE_FL_WAS_ENABLED_BIT, &file->flags);
		}
		break;
	}

	/* Enable or disable use of trace_buffered_event */
	if ((file_flags & EVENT_FILE_FL_SOFT_DISABLED) !=
	    (file->flags & EVENT_FILE_FL_SOFT_DISABLED)) {
		if (file->flags & EVENT_FILE_FL_SOFT_DISABLED)
			trace_buffered_event_enable();
		else
			trace_buffered_event_disable();
	}

	return ret;
}