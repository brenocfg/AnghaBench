#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ util_uint128_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 TYPE_1__ util_div128_32 (TYPE_1__,int /*<<< orphan*/ ) ; 
 TYPE_1__ util_mul64_64 (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static inline uint64_t audio_frames_to_ns(size_t sample_rate, uint64_t frames)
{
	util_uint128_t val;
	val = util_mul64_64(frames, 1000000000ULL);
	val = util_div128_32(val, (uint32_t)sample_rate);
	return val.low;
}