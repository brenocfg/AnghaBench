#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ samples_per_sec; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ audio_t ;

/* Variables and functions */

__attribute__((used)) static inline double ts_to_frames(const audio_t *audio, uint64_t ts)
{
	double audio_offset_d = (double)ts;
	audio_offset_d /= 1000000000.0;
	audio_offset_d *= (double)audio->info.samples_per_sec;

	return audio_offset_d;
}