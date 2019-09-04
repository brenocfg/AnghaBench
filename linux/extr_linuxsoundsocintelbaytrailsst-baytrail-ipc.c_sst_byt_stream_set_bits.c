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
struct TYPE_3__ {int pcm_wd_sz; } ;
struct TYPE_4__ {TYPE_1__ pcm_params; } ;
struct sst_byt_stream {TYPE_2__ request; } ;
struct sst_byt {int dummy; } ;

/* Variables and functions */

int sst_byt_stream_set_bits(struct sst_byt *byt, struct sst_byt_stream *stream,
			    int bits)
{
	stream->request.pcm_params.pcm_wd_sz = bits;
	return 0;
}