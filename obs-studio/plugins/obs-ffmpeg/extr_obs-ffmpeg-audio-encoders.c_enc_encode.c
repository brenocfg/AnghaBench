#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct encoder_packet {int dummy; } ;
struct encoder_frame {int /*<<< orphan*/ * data; } ;
struct enc_encoder {size_t audio_planes; int /*<<< orphan*/  frame_size_bytes; int /*<<< orphan*/ * samples; } ;

/* Variables and functions */
 int do_encode (struct enc_encoder*,struct encoder_packet*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool enc_encode(void *data, struct encoder_frame *frame,
		       struct encoder_packet *packet, bool *received_packet)
{
	struct enc_encoder *enc = data;

	for (size_t i = 0; i < enc->audio_planes; i++)
		memcpy(enc->samples[i], frame->data[i], enc->frame_size_bytes);

	return do_encode(enc, packet, received_packet);
}