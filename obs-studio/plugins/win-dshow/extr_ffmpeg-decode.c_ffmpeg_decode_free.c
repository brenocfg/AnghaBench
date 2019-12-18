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
struct ffmpeg_decode {scalar_t__ packet_buffer; scalar_t__ frame; scalar_t__ decoder; scalar_t__ hw_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (scalar_t__) ; 
 int /*<<< orphan*/  avcodec_close (scalar_t__) ; 
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ffmpeg_decode*,int /*<<< orphan*/ ,int) ; 

void ffmpeg_decode_free(struct ffmpeg_decode *decode)
{
	if (decode->hw_frame)
		av_free(decode->hw_frame);

	if (decode->decoder) {
		avcodec_close(decode->decoder);
		av_free(decode->decoder);
	}

	if (decode->frame)
		av_free(decode->frame);

	if (decode->packet_buffer)
		bfree(decode->packet_buffer);

	memset(decode, 0, sizeof(*decode));
}