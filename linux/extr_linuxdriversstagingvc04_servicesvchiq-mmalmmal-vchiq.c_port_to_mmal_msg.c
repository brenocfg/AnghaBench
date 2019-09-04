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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  num; } ;
struct TYPE_4__ {int /*<<< orphan*/  alignment; int /*<<< orphan*/  size; int /*<<< orphan*/  num; } ;
struct vchiq_mmal_port {TYPE_3__ current_buffer; TYPE_2__ recommended_buffer; TYPE_1__ minimum_buffer; int /*<<< orphan*/  enabled; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
struct mmal_port {scalar_t__ userdata; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_num; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  is_enabled; scalar_t__ index_all; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;

/* Variables and functions */

__attribute__((used)) static void port_to_mmal_msg(struct vchiq_mmal_port *port, struct mmal_port *p)
{
	/* todo do readonly fields need setting at all? */
	p->type = port->type;
	p->index = port->index;
	p->index_all = 0;
	p->is_enabled = port->enabled;
	p->buffer_num_min = port->minimum_buffer.num;
	p->buffer_size_min = port->minimum_buffer.size;
	p->buffer_alignment_min = port->minimum_buffer.alignment;
	p->buffer_num_recommended = port->recommended_buffer.num;
	p->buffer_size_recommended = port->recommended_buffer.size;

	/* only three writable fields in a port */
	p->buffer_num = port->current_buffer.num;
	p->buffer_size = port->current_buffer.size;
	p->userdata = (u32)(unsigned long)port;
}