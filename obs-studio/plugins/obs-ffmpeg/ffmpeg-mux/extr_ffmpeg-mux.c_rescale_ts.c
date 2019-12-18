#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_mux {int dummy; } ;
typedef  int int64_t ;
struct TYPE_7__ {int num; } ;
struct TYPE_6__ {int /*<<< orphan*/  time_base; TYPE_1__* codec; } ;
struct TYPE_5__ {TYPE_4__ time_base; } ;
typedef  TYPE_2__ AVStream ;

/* Variables and functions */
 int AV_ROUND_NEAR_INF ; 
 int AV_ROUND_PASS_MINMAX ; 
 int av_rescale_q_rnd (int,TYPE_4__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* get_stream (struct ffmpeg_mux*,int) ; 

__attribute__((used)) static inline int64_t rescale_ts(struct ffmpeg_mux *ffm, int64_t val, int idx)
{
	AVStream *stream = get_stream(ffm, idx);

	return av_rescale_q_rnd(val / stream->codec->time_base.num,
				stream->codec->time_base, stream->time_base,
				AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX);
}