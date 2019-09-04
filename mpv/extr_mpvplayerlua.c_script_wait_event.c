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
struct script_ctx {int /*<<< orphan*/  client; } ;
struct TYPE_9__ {char* prefix; char* level; char* text; int num_args; char** args; int const reason; scalar_t__ error; char* name; int id; int /*<<< orphan*/  result; int /*<<< orphan*/ * data; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ mpv_event_property ;
typedef  TYPE_1__ mpv_event_log_message ;
typedef  TYPE_1__ mpv_event_hook ;
typedef  TYPE_1__ mpv_event_end_file ;
typedef  TYPE_1__ mpv_event_command ;
typedef  TYPE_1__ mpv_event_client_message ;
struct TYPE_10__ {int event_id; double reply_userdata; scalar_t__ error; TYPE_1__* data; } ;
typedef  TYPE_7__ mpv_event ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  MPV_END_FILE_REASON_EOF 142 
#define  MPV_END_FILE_REASON_ERROR 141 
#define  MPV_END_FILE_REASON_QUIT 140 
#define  MPV_END_FILE_REASON_REDIRECT 139 
#define  MPV_END_FILE_REASON_STOP 138 
#define  MPV_EVENT_CLIENT_MESSAGE 137 
#define  MPV_EVENT_COMMAND_REPLY 136 
#define  MPV_EVENT_END_FILE 135 
#define  MPV_EVENT_HOOK 134 
#define  MPV_EVENT_LOG_MESSAGE 133 
#define  MPV_EVENT_PROPERTY_CHANGE 132 
#define  MPV_FORMAT_DOUBLE 131 
#define  MPV_FORMAT_FLAG 130 
#define  MPV_FORMAT_NODE 129 
#define  MPV_FORMAT_STRING 128 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* mpv_error_string (scalar_t__) ; 
 char* mpv_event_name (int) ; 
 TYPE_7__* mpv_wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int script_wait_event(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);

    mpv_event *event = mpv_wait_event(ctx->client, luaL_optnumber(L, 1, 1e20));

    lua_newtable(L); // event
    lua_pushstring(L, mpv_event_name(event->event_id)); // event name
    lua_setfield(L, -2, "event"); // event

    if (event->reply_userdata) {
        lua_pushnumber(L, event->reply_userdata);
        lua_setfield(L, -2, "id");
    }

    if (event->error < 0) {
        lua_pushstring(L, mpv_error_string(event->error)); // event err
        lua_setfield(L, -2, "error"); // event
    }

    switch (event->event_id) {
    case MPV_EVENT_LOG_MESSAGE: {
        mpv_event_log_message *msg = event->data;

        lua_pushstring(L, msg->prefix); // event s
        lua_setfield(L, -2, "prefix"); // event
        lua_pushstring(L, msg->level); // event s
        lua_setfield(L, -2, "level"); // event
        lua_pushstring(L, msg->text); // event s
        lua_setfield(L, -2, "text"); // event
        break;
    }
    case MPV_EVENT_CLIENT_MESSAGE: {
        mpv_event_client_message *msg = event->data;

        lua_newtable(L); // event args
        for (int n = 0; n < msg->num_args; n++) {
            lua_pushinteger(L, n + 1); // event args N
            lua_pushstring(L, msg->args[n]); // event args N val
            lua_settable(L, -3); // event args
        }
        lua_setfield(L, -2, "args"); // event
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
        lua_pushstring(L, reason); // event reason
        lua_setfield(L, -2, "reason"); // event

        if (eef->reason == MPV_END_FILE_REASON_ERROR) {
            lua_pushstring(L, mpv_error_string(eef->error)); // event error
            lua_setfield(L, -2, "error"); // event
        }
        break;
    }
    case MPV_EVENT_PROPERTY_CHANGE: {
        mpv_event_property *prop = event->data;
        lua_pushstring(L, prop->name);
        lua_setfield(L, -2, "name");
        switch (prop->format) {
        case MPV_FORMAT_NODE:
            pushnode(L, prop->data);
            break;
        case MPV_FORMAT_DOUBLE:
            lua_pushnumber(L, *(double *)prop->data);
            break;
        case MPV_FORMAT_FLAG:
            lua_pushboolean(L, *(int *)prop->data);
            break;
        case MPV_FORMAT_STRING:
            lua_pushstring(L, *(char **)prop->data);
            break;
        default:
            lua_pushnil(L);
        }
        lua_setfield(L, -2, "data");
        break;
    }
    case MPV_EVENT_HOOK: {
        mpv_event_hook *hook = event->data;
        lua_pushinteger(L, hook->id);
        lua_setfield(L, -2, "hook_id");
        break;
    }
    case MPV_EVENT_COMMAND_REPLY: {
        mpv_event_command *cmd = event->data;
        pushnode(L, &cmd->result);
        lua_setfield(L, -2, "result");
        break;
    }
    default: ;
    }

    // return event
    return 1;
}