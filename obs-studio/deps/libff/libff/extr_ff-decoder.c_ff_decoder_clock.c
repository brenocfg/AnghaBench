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
struct ff_decoder {double current_pts_time; double current_pts; } ;

/* Variables and functions */
 double av_gettime () ; 

double ff_decoder_clock(void *opaque)
{
	struct ff_decoder *decoder = opaque;
	double delta = (av_gettime() - decoder->current_pts_time) / 1000000.0;
	return decoder->current_pts + delta;
}