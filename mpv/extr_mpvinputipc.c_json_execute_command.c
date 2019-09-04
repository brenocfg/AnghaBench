#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct mpv_handle {int dummy; } ;
struct mp_log {int dummy; } ;
struct TYPE_23__ {char* string; TYPE_2__* list; } ;
struct TYPE_24__ {scalar_t__ format; TYPE_3__ u; } ;
typedef  TYPE_4__ mpv_node ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {char* string; int /*<<< orphan*/  int64; } ;
struct TYPE_25__ {scalar_t__ format; TYPE_1__ u; } ;
struct TYPE_22__ {int num; TYPE_7__* values; } ;

/* Variables and functions */
 int MPV_ERROR_INVALID_PARAMETER ; 
 int MPV_ERROR_SUCCESS ; 
 scalar_t__ MPV_FORMAT_INT64 ; 
 scalar_t__ MPV_FORMAT_NODE ; 
 scalar_t__ MPV_FORMAT_NODE_ARRAY ; 
 scalar_t__ MPV_FORMAT_NODE_MAP ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 int json_parse (void*,TYPE_4__*,char**,int) ; 
 int /*<<< orphan*/  json_write (char**,TYPE_4__*) ; 
 struct mp_log* mp_client_get_log (struct mpv_handle*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,char*) ; 
 int /*<<< orphan*/  mp_warn (struct mp_log*,char*) ; 
 int /*<<< orphan*/  mpv_client_api_version () ; 
 char* mpv_client_name (struct mpv_handle*) ; 
 int mpv_command_node (struct mpv_handle*,TYPE_4__*,TYPE_4__*) ; 
 char* mpv_error_string (int) ; 
 char* mpv_event_name (int) ; 
 int /*<<< orphan*/  mpv_free (char*) ; 
 int /*<<< orphan*/  mpv_free_node_contents (TYPE_4__*) ; 
 int mpv_get_property (struct mpv_handle*,char*,scalar_t__,TYPE_4__*) ; 
 char* mpv_get_property_string (struct mpv_handle*,char*) ; 
 int /*<<< orphan*/  mpv_get_time_us (struct mpv_handle*) ; 
 TYPE_4__* mpv_node_array_get (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_node_map_add (void*,TYPE_4__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  mpv_node_map_add_int64 (void*,TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_node_map_add_null (void*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  mpv_node_map_add_string (void*,TYPE_4__*,char*,char const*) ; 
 int mpv_observe_property (struct mpv_handle*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int mpv_request_event (struct mpv_handle*,int,int) ; 
 int mpv_request_log_messages (struct mpv_handle*,char*) ; 
 int mpv_set_property (struct mpv_handle*,char*,scalar_t__,TYPE_7__*) ; 
 int mpv_unobserve_property (struct mpv_handle*,int /*<<< orphan*/ ) ; 
 TYPE_4__* node_map_get (TYPE_4__*,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* ta_talloc_strdup_append (char*,char*) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static char *json_execute_command(struct mpv_handle *client, void *ta_parent,
                                  char *src)
{
    int rc;
    const char *cmd = NULL;
    struct mp_log *log = mp_client_get_log(client);

    mpv_node msg_node;
    mpv_node reply_node = {.format = MPV_FORMAT_NODE_MAP, .u.list = NULL};
    mpv_node *reqid_node = NULL;

    rc = json_parse(ta_parent, &msg_node, &src, 50);
    if (rc < 0) {
        mp_err(log, "malformed JSON received: '%s'\n", src);
        rc = MPV_ERROR_INVALID_PARAMETER;
        goto error;
    }

    if (msg_node.format != MPV_FORMAT_NODE_MAP) {
        rc = MPV_ERROR_INVALID_PARAMETER;
        goto error;
    }

    reqid_node = node_map_get(&msg_node, "request_id");
    if (reqid_node && reqid_node->format != MPV_FORMAT_INT64) {
        mp_warn(log, "'request_id' must be an integer. Using other types is "
                "deprecated and will trigger an error in the future!\n");
    }

    mpv_node *cmd_node = node_map_get(&msg_node, "command");
    if (!cmd_node ||
        (cmd_node->format != MPV_FORMAT_NODE_ARRAY) ||
        !cmd_node->u.list->num)
    {
        rc = MPV_ERROR_INVALID_PARAMETER;
        goto error;
    }

    mpv_node *cmd_str_node = mpv_node_array_get(cmd_node, 0);
    if (!cmd_str_node || (cmd_str_node->format != MPV_FORMAT_STRING)) {
        rc = MPV_ERROR_INVALID_PARAMETER;
        goto error;
    }

    cmd = cmd_str_node->u.string;

    if (!strcmp("client_name", cmd)) {
        const char *client_name = mpv_client_name(client);
        mpv_node_map_add_string(ta_parent, &reply_node, "data", client_name);
        rc = MPV_ERROR_SUCCESS;
    } else if (!strcmp("get_time_us", cmd)) {
        int64_t time_us = mpv_get_time_us(client);
        mpv_node_map_add_int64(ta_parent, &reply_node, "data", time_us);
        rc = MPV_ERROR_SUCCESS;
    } else if (!strcmp("get_version", cmd)) {
        int64_t ver = mpv_client_api_version();
        mpv_node_map_add_int64(ta_parent, &reply_node, "data", ver);
        rc = MPV_ERROR_SUCCESS;
    } else if (!strcmp("get_property", cmd)) {
        mpv_node result_node;

        if (cmd_node->u.list->num != 2) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_get_property(client, cmd_node->u.list->values[1].u.string,
                              MPV_FORMAT_NODE, &result_node);
        if (rc >= 0) {
            mpv_node_map_add(ta_parent, &reply_node, "data", &result_node);
            mpv_free_node_contents(&result_node);
        }
    } else if (!strcmp("get_property_string", cmd)) {
        if (cmd_node->u.list->num != 2) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        char *result = mpv_get_property_string(client,
                                        cmd_node->u.list->values[1].u.string);
        if (result) {
            mpv_node_map_add_string(ta_parent, &reply_node, "data", result);
            mpv_free(result);
        } else {
            mpv_node_map_add_null(ta_parent, &reply_node, "data");
        }
    } else if (!strcmp("set_property", cmd) ||
        !strcmp("set_property_string", cmd))
    {
        if (cmd_node->u.list->num != 3) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_set_property(client, cmd_node->u.list->values[1].u.string,
                              MPV_FORMAT_NODE, &cmd_node->u.list->values[2]);
    } else if (!strcmp("observe_property", cmd)) {
        if (cmd_node->u.list->num != 3) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_INT64) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[2].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_observe_property(client,
                                  cmd_node->u.list->values[1].u.int64,
                                  cmd_node->u.list->values[2].u.string,
                                  MPV_FORMAT_NODE);
    } else if (!strcmp("observe_property_string", cmd)) {
        if (cmd_node->u.list->num != 3) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_INT64) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[2].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_observe_property(client,
                                  cmd_node->u.list->values[1].u.int64,
                                  cmd_node->u.list->values[2].u.string,
                                  MPV_FORMAT_STRING);
    } else if (!strcmp("unobserve_property", cmd)) {
        if (cmd_node->u.list->num != 2) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_INT64) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_unobserve_property(client,
                                    cmd_node->u.list->values[1].u.int64);
    } else if (!strcmp("request_log_messages", cmd)) {
        if (cmd_node->u.list->num != 2) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        rc = mpv_request_log_messages(client,
                                      cmd_node->u.list->values[1].u.string);
    } else if (!strcmp("enable_event", cmd) ||
               !strcmp("disable_event", cmd))
    {
        bool enable = !strcmp("enable_event", cmd);

        if (cmd_node->u.list->num != 2) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        if (cmd_node->u.list->values[1].format != MPV_FORMAT_STRING) {
            rc = MPV_ERROR_INVALID_PARAMETER;
            goto error;
        }

        char *name = cmd_node->u.list->values[1].u.string;
        if (strcmp(name, "all") == 0) {
            for (int n = 0; n < 64; n++)
                mpv_request_event(client, n, enable);
            rc = MPV_ERROR_SUCCESS;
        } else {
            int event = -1;
            for (int n = 0; n < 64; n++) {
                const char *evname = mpv_event_name(n);
                if (evname && strcmp(evname, name) == 0)
                    event = n;
            }
            if (event < 0) {
                rc = MPV_ERROR_INVALID_PARAMETER;
                goto error;
            }
            rc = mpv_request_event(client, event, enable);
        }
    } else {
        mpv_node result_node;

        rc = mpv_command_node(client, cmd_node, &result_node);
        if (rc >= 0)
            mpv_node_map_add(ta_parent, &reply_node, "data", &result_node);
    }

error:
    /* If the request contains a "request_id", copy it back into the response.
     * This makes it easier on the requester to match up the IPC results with
     * the original requests.
     */
    if (reqid_node) {
        mpv_node_map_add(ta_parent, &reply_node, "request_id", reqid_node);
    } else {
        mpv_node_map_add_int64(ta_parent, &reply_node, "request_id", 0);
    }

    mpv_node_map_add_string(ta_parent, &reply_node, "error", mpv_error_string(rc));

    char *output = talloc_strdup(ta_parent, "");
    json_write(&output, &reply_node);
    output = ta_talloc_strdup_append(output, "\n");

    return output;
}