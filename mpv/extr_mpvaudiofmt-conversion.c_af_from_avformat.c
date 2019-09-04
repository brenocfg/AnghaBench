#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_2__ {int fmt; int sample_fmt; } ;

/* Variables and functions */
 TYPE_1__* audio_conversion_map ; 

int af_from_avformat(enum AVSampleFormat sample_fmt)
{
    for (int i = 0; audio_conversion_map[i].fmt; i++) {
        if (audio_conversion_map[i].sample_fmt == sample_fmt)
            return audio_conversion_map[i].fmt;
    }
    return 0;
}