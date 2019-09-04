#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_18__ {int /*<<< orphan*/  sync_mutex; TYPE_2__* remote; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  id; TYPE_4__* local; } ;
typedef  TYPE_3__ VCHIQ_STATE_T ;
struct TYPE_19__ {int /*<<< orphan*/  slot_sync; int /*<<< orphan*/  sync_release; } ;
typedef  TYPE_4__ VCHIQ_SHARED_STATE_T ;
struct TYPE_16__ {int fourcc; } ;
struct TYPE_20__ {TYPE_1__ base; } ;
typedef  TYPE_5__ VCHIQ_SERVICE_T ;
struct TYPE_21__ {int msgid; int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ VCHIQ_HEADER_T ;
struct TYPE_17__ {int /*<<< orphan*/  sync_trigger; } ;

/* Variables and functions */
 scalar_t__ SLOT_DATA_FROM_INDEX (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SRVTRACE_ENABLED (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_FOURCC_AS_4CHARS (int) ; 
 int /*<<< orphan*/  VCHIQ_LOG_INFO ; 
 scalar_t__ VCHIQ_LOG_TRACE ; 
 int VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
 int VCHIQ_MSGID_PADDING ; 
 int /*<<< orphan*/  VCHIQ_MSG_DSTPORT (int) ; 
 scalar_t__ VCHIQ_MSG_PAUSE ; 
 scalar_t__ VCHIQ_MSG_RESUME ; 
 int /*<<< orphan*/  VCHIQ_MSG_SRCPORT (int) ; 
 scalar_t__ VCHIQ_MSG_TYPE (int) ; 
 int /*<<< orphan*/  VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_ADD (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_INC (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_STATS_INC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 scalar_t__ copy_message_data (ssize_t (*) (void*,void*,size_t,size_t),void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_tx_bytes ; 
 int /*<<< orphan*/  ctrl_tx_count ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 
 int /*<<< orphan*/  msg_type_str (scalar_t__) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_wait (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_dump_mem (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vchiq_log_info (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_trace (scalar_t__,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vchiq_sync_log_level ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static VCHIQ_STATUS_T
queue_message_sync(VCHIQ_STATE_T *state, VCHIQ_SERVICE_T *service,
	int msgid,
	ssize_t (*copy_callback)(void *context, void *dest,
				 size_t offset, size_t maxsize),
	void *context,
	int size,
	int is_blocking)
{
	VCHIQ_SHARED_STATE_T *local;
	VCHIQ_HEADER_T *header;
	ssize_t callback_result;

	local = state->local;

	if ((VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_RESUME) &&
		(mutex_lock_killable(&state->sync_mutex) != 0))
		return VCHIQ_RETRY;

	remote_event_wait(state, &local->sync_release);

	rmb();

	header = (VCHIQ_HEADER_T *)SLOT_DATA_FROM_INDEX(state,
		local->slot_sync);

	{
		int oldmsgid = header->msgid;

		if (oldmsgid != VCHIQ_MSGID_PADDING)
			vchiq_log_error(vchiq_core_log_level,
				"%d: qms - msgid %x, not PADDING",
				state->id, oldmsgid);
	}

	vchiq_log_info(vchiq_sync_log_level,
		       "%d: qms %s@%pK,%x (%d->%d)", state->id,
		       msg_type_str(VCHIQ_MSG_TYPE(msgid)),
		       header, size, VCHIQ_MSG_SRCPORT(msgid),
		       VCHIQ_MSG_DSTPORT(msgid));

	callback_result =
		copy_message_data(copy_callback, context,
				  header->data, size);

	if (callback_result < 0) {
		mutex_unlock(&state->slot_mutex);
		VCHIQ_SERVICE_STATS_INC(service,
					error_count);
		return VCHIQ_ERROR;
	}

	if (service) {
		if (SRVTRACE_ENABLED(service,
				     VCHIQ_LOG_INFO))
			vchiq_log_dump_mem("Sent", 0,
					   header->data,
					   min((size_t)16,
					       (size_t)callback_result));

		VCHIQ_SERVICE_STATS_INC(service, ctrl_tx_count);
		VCHIQ_SERVICE_STATS_ADD(service, ctrl_tx_bytes, size);
	} else {
		VCHIQ_STATS_INC(state, ctrl_tx_count);
	}

	header->size = size;
	header->msgid = msgid;

	if (vchiq_sync_log_level >= VCHIQ_LOG_TRACE) {
		int svc_fourcc;

		svc_fourcc = service
			? service->base.fourcc
			: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');

		vchiq_log_trace(vchiq_sync_log_level,
			"Sent Sync Msg %s(%u) to %c%c%c%c s:%u d:%d len:%d",
			msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			VCHIQ_MSG_TYPE(msgid),
			VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
			VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid),
			size);
	}

	/* Make sure the new header is visible to the peer. */
	wmb();

	remote_event_signal(&state->remote->sync_trigger);

	if (VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_PAUSE)
		mutex_unlock(&state->sync_mutex);

	return VCHIQ_SUCCESS;
}