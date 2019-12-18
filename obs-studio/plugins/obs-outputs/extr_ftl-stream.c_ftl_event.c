#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ftl_stream {int /*<<< orphan*/  output; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ reason; int /*<<< orphan*/  error_code; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
struct TYPE_7__ {TYPE_2__ msg; } ;
typedef  TYPE_3__ ftl_status_msg_t ;
typedef  enum ret_type { ____Placeholder_ret_type } ret_type ;

/* Variables and functions */
 scalar_t__ FTL_STATUS_EVENT_REASON_API_REQUEST ; 
 scalar_t__ FTL_STATUS_EVENT_TYPE_DISCONNECTED ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  OBS_OUTPUT_DISCONNECTED ; 
 int RET_BREAK ; 
 int RET_CONTINUE ; 
 int RET_EXIT ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ftl_status_code_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ret_type ftl_event(struct ftl_stream *stream,
			       ftl_status_msg_t status)
{
	if (status.msg.event.type != FTL_STATUS_EVENT_TYPE_DISCONNECTED)
		return RET_CONTINUE;

	info("Disconnected from ingest with reason: %s",
	     ftl_status_code_to_string(status.msg.event.error_code));

	if (status.msg.event.reason == FTL_STATUS_EVENT_REASON_API_REQUEST) {
		return RET_BREAK;
	}

	//tell OBS and it will trigger a reconnection
	blog(LOG_WARNING, "Reconnecting to Ingest");
	obs_output_signal_stop(stream->output, OBS_OUTPUT_DISCONNECTED);
	return RET_EXIT;
}