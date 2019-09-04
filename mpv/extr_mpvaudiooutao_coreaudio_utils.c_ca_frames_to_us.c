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
typedef  float uint32_t ;
struct ao {scalar_t__ samplerate; } ;
typedef  float int64_t ;

/* Variables and functions */

int64_t ca_frames_to_us(struct ao *ao, uint32_t frames)
{
    return frames / (float) ao->samplerate * 1e6;
}