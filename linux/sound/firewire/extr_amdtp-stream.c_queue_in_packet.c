#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_iso_packet {int skip; int /*<<< orphan*/  payload_length; int /*<<< orphan*/  header_length; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_ctx_payload_length; int /*<<< orphan*/  ctx_header_size; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct amdtp_stream {TYPE_2__ ctx_data; } ;

/* Variables and functions */
 int queue_packet (struct amdtp_stream*,struct fw_iso_packet*) ; 

__attribute__((used)) static inline int queue_in_packet(struct amdtp_stream *s,
				  struct fw_iso_packet *params)
{
	// Queue one packet for IR context.
	params->header_length = s->ctx_data.tx.ctx_header_size;
	params->payload_length = s->ctx_data.tx.max_ctx_payload_length;
	params->skip = false;
	return queue_packet(s, params);
}