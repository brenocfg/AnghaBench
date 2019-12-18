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
struct TYPE_2__ {unsigned long (* c_resolution ) (struct snd_timer*) ;unsigned long resolution; } ;
struct snd_timer {TYPE_1__ hw; } ;

/* Variables and functions */
 unsigned long stub1 (struct snd_timer*) ; 

__attribute__((used)) static unsigned long snd_timer_hw_resolution(struct snd_timer *timer)
{
	if (timer->hw.c_resolution)
		return timer->hw.c_resolution(timer);
	else
		return timer->hw.resolution;
}