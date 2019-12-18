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
struct snd_timer {int dummy; } ;
struct snd_cs4231 {int* image; } ;

/* Variables and functions */
 size_t CS4231_PLAYBK_FORMAT ; 
 struct snd_cs4231* snd_timer_chip (struct snd_timer*) ; 

__attribute__((used)) static unsigned long snd_cs4231_timer_resolution(struct snd_timer *timer)
{
	struct snd_cs4231 *chip = snd_timer_chip(timer);

	return chip->image[CS4231_PLAYBK_FORMAT] & 1 ? 9969 : 9920;
}