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
struct vchiq_mmal_port {struct mmal_msg_context* event_context; } ;
struct TYPE_4__ {TYPE_3__* buffer; } ;
struct TYPE_5__ {TYPE_1__ bulk; } ;
struct mmal_msg_context {TYPE_2__ u; } ;
struct TYPE_6__ {struct TYPE_6__* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  release_msg_context (struct mmal_msg_context*) ; 

__attribute__((used)) static void free_event_context(struct vchiq_mmal_port *port)
{
	struct mmal_msg_context *ctx = port->event_context;

	kfree(ctx->u.bulk.buffer->buffer);
	kfree(ctx->u.bulk.buffer);
	release_msg_context(ctx);
}