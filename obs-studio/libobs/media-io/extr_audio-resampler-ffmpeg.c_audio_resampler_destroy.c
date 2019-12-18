#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* output_buffer; scalar_t__ context; } ;
typedef  TYPE_1__ audio_resampler_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  swr_free (scalar_t__*) ; 

void audio_resampler_destroy(audio_resampler_t *rs)
{
	if (rs) {
		if (rs->context)
			swr_free(&rs->context);
		if (rs->output_buffer[0])
			av_freep(&rs->output_buffer[0]);

		bfree(rs);
	}
}