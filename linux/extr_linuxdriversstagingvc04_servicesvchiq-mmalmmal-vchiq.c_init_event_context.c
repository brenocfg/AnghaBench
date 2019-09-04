#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vchiq_mmal_port {struct mmal_msg_context* event_context; int /*<<< orphan*/  event_context_mutex; } ;
struct vchiq_mmal_instance {int dummy; } ;
struct TYPE_4__ {TYPE_3__* buffer; int /*<<< orphan*/  work; struct vchiq_mmal_port* port; struct vchiq_mmal_instance* instance; } ;
struct TYPE_5__ {TYPE_1__ bulk; } ;
struct mmal_msg_context {TYPE_2__ u; } ;
struct TYPE_6__ {void* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MMAL_WORKER_EVENT_SPACE ; 
 int /*<<< orphan*/  buffer_work_cb ; 
 struct mmal_msg_context* get_msg_context (struct vchiq_mmal_instance*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_msg_context (struct mmal_msg_context*) ; 

__attribute__((used)) static void init_event_context(struct vchiq_mmal_instance *instance,
			       struct vchiq_mmal_port *port)
{
	struct mmal_msg_context *ctx = get_msg_context(instance);

	mutex_init(&port->event_context_mutex);

	port->event_context = ctx;
	ctx->u.bulk.instance = instance;
	ctx->u.bulk.port = port;
	ctx->u.bulk.buffer =
		kzalloc(sizeof(*ctx->u.bulk.buffer), GFP_KERNEL);
	if (!ctx->u.bulk.buffer)
		goto release_msg_context;
	ctx->u.bulk.buffer->buffer = kzalloc(MMAL_WORKER_EVENT_SPACE,
					     GFP_KERNEL);
	if (!ctx->u.bulk.buffer->buffer)
		goto release_buffer;

	INIT_WORK(&ctx->u.bulk.work, buffer_work_cb);
	return;

release_buffer:
	kfree(ctx->u.bulk.buffer);
release_msg_context:
	release_msg_context(ctx);
}