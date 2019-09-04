#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * list; } ;
struct TYPE_18__ {TYPE_1__ u; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ mpv_node ;
struct TYPE_19__ {char* prefix; char* level; char* text; int num_args; char* name; TYPE_2__* data; int /*<<< orphan*/  format; int /*<<< orphan*/ * args; } ;
typedef  TYPE_3__ mpv_event_property ;
typedef  TYPE_3__ mpv_event_log_message ;
typedef  TYPE_3__ mpv_event_client_message ;
struct TYPE_20__ {int event_id; scalar_t__ error; TYPE_3__* data; scalar_t__ reply_userdata; } ;
typedef  TYPE_6__ mpv_event ;

/* Variables and functions */
#define  MPV_EVENT_CLIENT_MESSAGE 134 
#define  MPV_EVENT_LOG_MESSAGE 133 
#define  MPV_EVENT_PROPERTY_CHANGE 132 
#define  MPV_FORMAT_DOUBLE 131 
#define  MPV_FORMAT_FLAG 130 
#define  MPV_FORMAT_NODE 129 
 int /*<<< orphan*/  MPV_FORMAT_NODE_ARRAY ; 
#define  MPV_FORMAT_STRING 128 
 char* mpv_error_string (scalar_t__) ; 
 char* mpv_event_name (int) ; 
 int /*<<< orphan*/  mpv_node_array_add_string (void*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_node_map_add (void*,TYPE_2__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpv_node_map_add_double (void*,TYPE_2__*,char*,double) ; 
 int /*<<< orphan*/  mpv_node_map_add_flag (void*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  mpv_node_map_add_int64 (void*,TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mpv_node_map_add_null (void*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mpv_node_map_add_string (void*,TYPE_2__*,char*,char*) ; 

__attribute__((used)) static void mpv_event_to_node(void *ta_parent, mpv_event *event, mpv_node *dst)
{
    mpv_node_map_add_string(ta_parent, dst, "event", mpv_event_name(event->event_id));

    if (event->reply_userdata)
        mpv_node_map_add_int64(ta_parent, dst, "id", event->reply_userdata);

    if (event->error < 0)
        mpv_node_map_add_string(ta_parent, dst, "error", mpv_error_string(event->error));

    switch (event->event_id) {
    case MPV_EVENT_LOG_MESSAGE: {
        mpv_event_log_message *msg = event->data;

        mpv_node_map_add_string(ta_parent, dst, "prefix", msg->prefix);
        mpv_node_map_add_string(ta_parent, dst, "level",  msg->level);
        mpv_node_map_add_string(ta_parent, dst, "text",   msg->text);

        break;
    }

    case MPV_EVENT_CLIENT_MESSAGE: {
        mpv_event_client_message *msg = event->data;

        mpv_node args_node = {.format = MPV_FORMAT_NODE_ARRAY, .u.list = NULL};
        for (int n = 0; n < msg->num_args; n++)
            mpv_node_array_add_string(ta_parent, &args_node, msg->args[n]);
        mpv_node_map_add(ta_parent, dst, "args", &args_node);
        break;
    }

    case MPV_EVENT_PROPERTY_CHANGE: {
        mpv_event_property *prop = event->data;

        mpv_node_map_add_string(ta_parent, dst, "name", prop->name);

        switch (prop->format) {
        case MPV_FORMAT_NODE:
            mpv_node_map_add(ta_parent, dst, "data", prop->data);
            break;
        case MPV_FORMAT_DOUBLE:
            mpv_node_map_add_double(ta_parent, dst, "data", *(double *)prop->data);
            break;
        case MPV_FORMAT_FLAG:
            mpv_node_map_add_flag(ta_parent, dst, "data", *(int *)prop->data);
            break;
        case MPV_FORMAT_STRING:
            mpv_node_map_add_string(ta_parent, dst, "data", *(char **)prop->data);
            break;
        default:
            mpv_node_map_add_null(ta_parent, dst, "data");
        }
        break;
    }
    }
}