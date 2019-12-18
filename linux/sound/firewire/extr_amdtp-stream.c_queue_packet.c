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
struct fw_iso_packet {scalar_t__ sy; int /*<<< orphan*/  tag; int /*<<< orphan*/  interrupt; } ;
struct TYPE_5__ {TYPE_1__* packets; int /*<<< orphan*/  iso_buffer; } ;
struct amdtp_stream {int packet_index; TYPE_3__* unit; TYPE_2__ buffer; int /*<<< orphan*/  context; int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_INTERVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 size_t QUEUE_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int fw_iso_context_queue (int /*<<< orphan*/ ,struct fw_iso_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_packet(struct amdtp_stream *s, struct fw_iso_packet *params)
{
	int err;

	params->interrupt = IS_ALIGNED(s->packet_index + 1, INTERRUPT_INTERVAL);
	params->tag = s->tag;
	params->sy = 0;

	err = fw_iso_context_queue(s->context, params, &s->buffer.iso_buffer,
				   s->buffer.packets[s->packet_index].offset);
	if (err < 0) {
		dev_err(&s->unit->device, "queueing error: %d\n", err);
		goto end;
	}

	if (++s->packet_index >= QUEUE_LENGTH)
		s->packet_index = 0;
end:
	return err;
}