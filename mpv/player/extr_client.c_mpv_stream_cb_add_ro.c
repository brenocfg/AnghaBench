#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_custom_protocol {void* user_data; int /*<<< orphan*/  open_fn; int /*<<< orphan*/  protocol; } ;
struct mp_client_api {int num_custom_protocols; int /*<<< orphan*/  lock; struct mp_custom_protocol* custom_protocols; } ;
typedef  int /*<<< orphan*/  mpv_stream_cb_open_ro_fn ;
struct TYPE_3__ {struct mp_client_api* clients; } ;
typedef  TYPE_1__ mpv_handle ;

/* Variables and functions */
 int MPV_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_client_api*,struct mp_custom_protocol*,int,struct mp_custom_protocol) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ stream_has_proto (char const*) ; 
 int /*<<< orphan*/  talloc_strdup (struct mp_client_api*,char const*) ; 

int mpv_stream_cb_add_ro(mpv_handle *ctx, const char *protocol, void *user_data,
                         mpv_stream_cb_open_ro_fn open_fn)
{
    if (!open_fn)
        return MPV_ERROR_INVALID_PARAMETER;

    struct mp_client_api *clients = ctx->clients;
    int r = 0;
    pthread_mutex_lock(&clients->lock);
    for (int n = 0; n < clients->num_custom_protocols; n++) {
        struct mp_custom_protocol *proto = &clients->custom_protocols[n];
        if (strcmp(proto->protocol, protocol) == 0) {
            r = MPV_ERROR_INVALID_PARAMETER;
            break;
        }
    }
    if (stream_has_proto(protocol))
        r = MPV_ERROR_INVALID_PARAMETER;
    if (r >= 0) {
        struct mp_custom_protocol proto = {
            .protocol = talloc_strdup(clients, protocol),
            .user_data = user_data,
            .open_fn = open_fn,
        };
        MP_TARRAY_APPEND(clients, clients->custom_protocols,
                         clients->num_custom_protocols, proto);
    }
    pthread_mutex_unlock(&clients->lock);
    return r;
}