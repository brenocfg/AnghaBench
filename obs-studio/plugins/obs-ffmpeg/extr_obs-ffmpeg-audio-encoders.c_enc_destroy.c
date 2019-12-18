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
struct enc_encoder {int /*<<< orphan*/  packet_buffer; scalar_t__ aframe; scalar_t__ context; scalar_t__* samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  avcodec_close (scalar_t__) ; 
 int /*<<< orphan*/  bfree (struct enc_encoder*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc_destroy(void *data)
{
	struct enc_encoder *enc = data;

	if (enc->samples[0])
		av_freep(&enc->samples[0]);
	if (enc->context)
		avcodec_close(enc->context);
	if (enc->aframe)
		av_frame_free(&enc->aframe);

	da_free(enc->packet_buffer);
	bfree(enc);
}