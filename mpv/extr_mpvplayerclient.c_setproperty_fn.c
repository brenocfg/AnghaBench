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
struct setproperty_request {scalar_t__ format; int /*<<< orphan*/  userdata; scalar_t__ reply_ctx; int /*<<< orphan*/  status; int /*<<< orphan*/  mpctx; int /*<<< orphan*/  name; struct mpv_node* data; } ;
struct mpv_node {scalar_t__ format; int /*<<< orphan*/  u; } ;
struct mpv_event {int /*<<< orphan*/  error; int /*<<< orphan*/  event_id; } ;
struct m_option {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_SET_PROPERTY_REPLY ; 
 scalar_t__ MPV_FORMAT_NODE ; 
 int /*<<< orphan*/  M_PROPERTY_SET_NODE ; 
 struct m_option* get_mp_type (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mpv_node*,int /*<<< orphan*/ ) ; 
 int mp_property_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpv_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_reply (scalar_t__,int /*<<< orphan*/ ,struct mpv_event*) ; 
 int /*<<< orphan*/  talloc_free (struct setproperty_request*) ; 
 int /*<<< orphan*/  translate_property_error (int) ; 

__attribute__((used)) static void setproperty_fn(void *arg)
{
    struct setproperty_request *req = arg;
    const struct m_option *type = get_mp_type(req->format);

    struct mpv_node *node;
    struct mpv_node tmp;
    if (req->format == MPV_FORMAT_NODE) {
        node = req->data;
    } else {
        tmp.format = req->format;
        memcpy(&tmp.u, req->data, type->type->size);
        node = &tmp;
    }

    int err = mp_property_do(req->name, M_PROPERTY_SET_NODE, node, req->mpctx);

    req->status = translate_property_error(err);

    if (req->reply_ctx) {
        struct mpv_event reply = {
            .event_id = MPV_EVENT_SET_PROPERTY_REPLY,
            .error = req->status,
        };
        send_reply(req->reply_ctx, req->userdata, &reply);
        talloc_free(req);
    }
}