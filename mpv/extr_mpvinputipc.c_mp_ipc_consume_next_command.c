#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mpv_handle {int dummy; } ;
struct TYPE_9__ {char* start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 TYPE_1__ bstr_getline (TYPE_1__,TYPE_1__*) ; 
 TYPE_1__ bstrdup (int /*<<< orphan*/ *,TYPE_1__) ; 
 char* bstrto0 (void*,TYPE_1__) ; 
 char* json_execute_command (struct mpv_handle*,void*,char*) ; 
 int /*<<< orphan*/  json_skip_whitespace (char**) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_steal (void*,char*) ; 
 char* text_execute_command (struct mpv_handle*,void*,char*) ; 

char *mp_ipc_consume_next_command(struct mpv_handle *client, void *ctx, bstr *buf)
{
    void *tmp = talloc_new(NULL);

    bstr rest;
    bstr line = bstr_getline(*buf, &rest);
    char *line0 = bstrto0(tmp, line);
    talloc_steal(tmp, buf->start);
    *buf = bstrdup(NULL, rest);

    json_skip_whitespace(&line0);

    char *reply_msg = NULL;
    if (line0[0] == '\0' || line0[0] == '#') {
        // skip
    } else if (line0[0] == '{') {
        reply_msg = json_execute_command(client, tmp, line0);
    } else {
        reply_msg = text_execute_command(client, tmp, line0);
    }

    talloc_steal(ctx, reply_msg);
    talloc_free(tmp);
    return reply_msg;
}