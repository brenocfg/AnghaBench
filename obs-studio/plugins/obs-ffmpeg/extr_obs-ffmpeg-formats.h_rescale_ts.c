#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  time_base; } ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AV_ROUND_NEAR_INF ; 
 int AV_ROUND_PASS_MINMAX ; 
 int /*<<< orphan*/  av_rescale_q_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int64_t rescale_ts(int64_t val, AVCodecContext *context,
				 AVRational new_base)
{
	return av_rescale_q_rnd(val, context->time_base, new_base,
				AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX);
}