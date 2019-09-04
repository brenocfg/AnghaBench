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
struct TYPE_4__ {int /*<<< orphan*/  audio_fd; } ;
struct TYPE_5__ {int req_samplerate; int samplerate; TYPE_1__ oss; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNDCTL_DSP_SPEED ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int ai_oss_set_samplerate(audio_in_t *ai)
{
    int tmp = ai->req_samplerate;
    if (ioctl(ai->oss.audio_fd, SNDCTL_DSP_SPEED, &tmp) == -1) return -1;
    ai->samplerate = tmp;
    return 0;
}