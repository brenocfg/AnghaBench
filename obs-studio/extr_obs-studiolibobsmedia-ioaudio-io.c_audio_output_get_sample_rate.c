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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  samples_per_sec; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ audio_t ;

/* Variables and functions */

uint32_t audio_output_get_sample_rate(const audio_t *audio)
{
	return audio ? audio->info.samples_per_sec : 0;
}