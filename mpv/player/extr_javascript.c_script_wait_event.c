#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* prefix; char* level; char* text; int num_args; char** args; int const reason; scalar_t__ error; char* name; double id; int /*<<< orphan*/  result; int /*<<< orphan*/ * data; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ mpv_event_property ;
typedef  TYPE_1__ mpv_event_log_message ;
typedef  TYPE_1__ mpv_event_hook ;
typedef  TYPE_1__ mpv_event_end_file ;
typedef  TYPE_1__ mpv_event_command ;
typedef  TYPE_1__ mpv_event_client_message ;
struct TYPE_10__ {int event_id; double reply_userdata; scalar_t__ error; TYPE_1__* data; } ;
typedef  TYPE_7__ mpv_event ;
typedef  int /*<<< orphan*/  js_State ;
typedef  double int64_t ;

/* Variables and functions */
#define  MPV_END_FILE_REASON_EOF 143 
#define  MPV_END_FILE_REASON_ERROR 142 
#define  MPV_END_FILE_REASON_QUIT 141 
#define  MPV_END_FILE_REASON_REDIRECT 140 
#define  MPV_END_FILE_REASON_STOP 139 
#define  MPV_EVENT_CLIENT_MESSAGE 138 
#define  MPV_EVENT_COMMAND_REPLY 137 
#define  MPV_EVENT_END_FILE 136 
#define  MPV_EVENT_HOOK 135 
#define  MPV_EVENT_LOG_MESSAGE 134 
#define  MPV_EVENT_PROPERTY_CHANGE 133 
#define  MPV_FORMAT_DOUBLE 132 
#define  MPV_FORMAT_FLAG 131 
#define  MPV_FORMAT_INT64 130 
#define  MPV_FORMAT_NODE 129 
#define  MPV_FORMAT_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jclient (int /*<<< orphan*/ *) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 int js_tonumber (int /*<<< orphan*/ *,int) ; 
 char* mpv_error_string (scalar_t__) ; 
 char* mpv_event_name (int) ; 
 TYPE_7__* mpv_wait_event (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_wait_event(js_State *J)
{
    int top = js_gettop(J);
    double timeout = js_isnumber(J, 1) ? js_tonumber(J, 1) : -1;
    mpv_event *event = mpv_wait_event(jclient(J), timeout);

    js_newobject(J); // the reply
    js_pushstring(J, mpv_event_name(event->event_id));
    js_setproperty(J, -2, "event");  // reply.event (is an event name)

    if (event->reply_userdata) {
        js_pushnumber(J, event->reply_userdata);
        js_setproperty(J, -2, "id");   // reply.id
    }

    if (event->error < 0) {
        // TODO: untested
        js_pushstring(J, mpv_error_string(event->error));
        js_setproperty(J, -2, "error");  // reply.error
    }

    switch (event->event_id) {
    case MPV_EVENT_LOG_MESSAGE: {
        mpv_event_log_message *msg = event->data;

        js_pushstring(J, msg->prefix);
        js_setproperty(J, -2, "prefix");  // reply.prefix (e.g. "cplayer")
        js_pushstring(J, msg->level);
        js_setproperty(J, -2, "level");  // reply.level (e.g. "v" or "info")
        js_pushstring(J, msg->text);
        js_setproperty(J, -2, "text");  // reply.text
        break;
    }

    case MPV_EVENT_CLIENT_MESSAGE: {
        mpv_event_client_message *msg = event->data;

        js_newarray(J);  // reply.args
        for (int n = 0; n < msg->num_args; n++) {
            js_pushstring(J, msg->args[n]);
            js_setindex(J, -2, n);
        }
        js_setproperty(J, -2, "args");  // reply.args (is a strings array)
        break;
    }

    case MPV_EVENT_END_FILE: {
        mpv_event_end_file *eef = event->data;
        const char *reason;

        switch (eef->reason) {
        case MPV_END_FILE_REASON_EOF: reason = "eof"; break;
        case MPV_END_FILE_REASON_STOP: reason = "stop"; break;
        case MPV_END_FILE_REASON_QUIT: reason = "quit"; break;
        case MPV_END_FILE_REASON_ERROR: reason = "error"; break;
        case MPV_END_FILE_REASON_REDIRECT: reason = "redirect"; break;
        default:
            reason = "unknown";
        }
        js_pushstring(J, reason);
        js_setproperty(J, -2, "reason");  // reply.reason

        if (eef->reason == MPV_END_FILE_REASON_ERROR) {
            js_pushstring(J, mpv_error_string(eef->error));
            js_setproperty(J, -2, "error");  // reply.error
        }
        break;
    }

    case MPV_EVENT_PROPERTY_CHANGE: {
        mpv_event_property *prop = event->data;
        js_pushstring(J, prop->name);
        js_setproperty(J, -2, "name");  // reply.name (is a property name)

        switch (prop->format) {
        case MPV_FORMAT_NODE:   pushnode(J, prop->data); break;
        case MPV_FORMAT_DOUBLE: js_pushnumber(J, *(double *)prop->data); break;
        case MPV_FORMAT_INT64:  js_pushnumber(J, *(int64_t *)prop->data); break;
        case MPV_FORMAT_FLAG:   js_pushboolean(J, *(int *)prop->data); break;
        case MPV_FORMAT_STRING: js_pushstring(J, *(char **)prop->data); break;
        default:
            js_pushnull(J);  // also for FORMAT_NONE, e.g. observe type "none"
        }
        js_setproperty(J, -2, "data");  // reply.data (value as observed type)
        break;
    }

    case MPV_EVENT_HOOK: {
        mpv_event_hook *hook = event->data;
        js_pushnumber(J, hook->id);
        js_setproperty(J, -2, "hook_id");  // reply.hook_id (is a number)
        break;
    }

    case MPV_EVENT_COMMAND_REPLY: {
        mpv_event_command *cmd = event->data;
        pushnode(J, &cmd->result);
        js_setproperty(J, -2, "result");  // reply.result (mpv node)
        break;
    }
    }  // switch (event->event_id)

    assert(top == js_gettop(J) - 1);
}