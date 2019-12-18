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
struct TYPE_2__ {scalar_t__ type; } ;
struct obs_encoder {TYPE_1__ info; } ;
struct encoder_packet {int dummy; } ;
struct encoder_callback {int /*<<< orphan*/  param; int /*<<< orphan*/  (* new_packet ) (int /*<<< orphan*/ ,struct encoder_packet*) ;int /*<<< orphan*/  sent_first_packet; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  send_first_video_packet (struct obs_encoder*,struct encoder_callback*,struct encoder_packet*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct encoder_packet*) ; 

__attribute__((used)) static inline void send_packet(struct obs_encoder *encoder,
			       struct encoder_callback *cb,
			       struct encoder_packet *packet)
{
	/* include SEI in first video packet */
	if (encoder->info.type == OBS_ENCODER_VIDEO && !cb->sent_first_packet)
		send_first_video_packet(encoder, cb, packet);
	else
		cb->new_packet(cb->param, packet);
}