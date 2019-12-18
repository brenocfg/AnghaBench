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
struct dbus_sleep_info {scalar_t__ id; int type; int /*<<< orphan*/  c; int /*<<< orphan*/ * pending; TYPE_1__* service; } ;
typedef  int dbus_uint32_t ;
typedef  scalar_t__ dbus_bool_t ;
struct TYPE_2__ {char* uninhibit; int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
#define  GNOME_SM 129 
 int /*<<< orphan*/  LOG_ERROR ; 
#define  MATE_SM 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbus_connection_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_connection_send_with_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 scalar_t__ dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_method_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_pending_call_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_pending_call_steal_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_pending_call_unref (int /*<<< orphan*/ *) ; 

void dbus_inhibit_sleep(struct dbus_sleep_info *info, const char *reason,
			bool active)
{
	DBusMessage *reply;
	const char *method;
	dbus_bool_t success;

	if (info->pending) {

		dbus_pending_call_block(info->pending);
		reply = dbus_pending_call_steal_reply(info->pending);
		dbus_pending_call_unref(info->pending);
		info->pending = NULL;

		if (reply) {
			success = dbus_message_get_args(reply, NULL,
							DBUS_TYPE_UINT32,
							&info->id,
							DBUS_TYPE_INVALID);
			if (!success)
				info->id = 0;
			dbus_message_unref(reply);
		}
	}

	if (active == !!info->id)
		return;

	method = active ? "Inhibit" : info->service->uninhibit;

	reply = dbus_message_new_method_call(info->service->name,
					     info->service->path,
					     info->service->name, method);
	if (reply == NULL) {
		blog(LOG_ERROR, "dbus_message_new_method_call failed");
		return;
	}

	if (active) {
		const char *program = "libobs";
		dbus_uint32_t flags = 0xC;
		dbus_uint32_t xid = 0;

		assert(info->id == 0);

		switch (info->type) {
		case MATE_SM:
		case GNOME_SM:
			success = dbus_message_append_args(
				reply, DBUS_TYPE_STRING, &program,
				DBUS_TYPE_UINT32, &xid, DBUS_TYPE_STRING,
				&reason, DBUS_TYPE_UINT32, &flags,
				DBUS_TYPE_INVALID);
			break;
		default:
			success = dbus_message_append_args(
				reply, DBUS_TYPE_STRING, &program,
				DBUS_TYPE_STRING, &reason, DBUS_TYPE_INVALID);
		}

		if (success) {
			success = dbus_connection_send_with_reply(
				info->c, reply, &info->pending, -1);
			if (!success)
				info->pending = NULL;
		}
	} else {
		assert(info->id != 0);
		success = dbus_message_append_args(
			reply, DBUS_TYPE_UINT32, &info->id, DBUS_TYPE_INVALID);
		if (success)
			success = dbus_connection_send(info->c, reply, NULL);
		if (!success)
			info->id = 0;
	}

	dbus_connection_flush(info->c);
	dbus_message_unref(reply);
}