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

/* Variables and functions */
 int /*<<< orphan*/  BAD_EVENT_NAME ; 
 int /*<<< orphan*/  BAD_GROUP_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  EVENT_TOO_LONG ; 
 int /*<<< orphan*/  GROUP_TOO_LONG ; 
 int MAX_EVENT_NAME_LEN ; 
 int /*<<< orphan*/  NO_EVENT_NAME ; 
 int /*<<< orphan*/  NO_GROUP_NAME ; 
 int /*<<< orphan*/  is_good_name (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  trace_probe_log_err (int,int /*<<< orphan*/ ) ; 

int traceprobe_parse_event_name(const char **pevent, const char **pgroup,
				char *buf, int offset)
{
	const char *slash, *event = *pevent;
	int len;

	slash = strchr(event, '/');
	if (slash) {
		if (slash == event) {
			trace_probe_log_err(offset, NO_GROUP_NAME);
			return -EINVAL;
		}
		if (slash - event + 1 > MAX_EVENT_NAME_LEN) {
			trace_probe_log_err(offset, GROUP_TOO_LONG);
			return -EINVAL;
		}
		strlcpy(buf, event, slash - event + 1);
		if (!is_good_name(buf)) {
			trace_probe_log_err(offset, BAD_GROUP_NAME);
			return -EINVAL;
		}
		*pgroup = buf;
		*pevent = slash + 1;
		offset += slash - event + 1;
		event = *pevent;
	}
	len = strlen(event);
	if (len == 0) {
		trace_probe_log_err(offset, NO_EVENT_NAME);
		return -EINVAL;
	} else if (len > MAX_EVENT_NAME_LEN) {
		trace_probe_log_err(offset, EVENT_TOO_LONG);
		return -EINVAL;
	}
	if (!is_good_name(event)) {
		trace_probe_log_err(offset, BAD_EVENT_NAME);
		return -EINVAL;
	}
	return 0;
}