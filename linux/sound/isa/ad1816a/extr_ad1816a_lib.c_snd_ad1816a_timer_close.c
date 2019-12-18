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
struct snd_ad1816a {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_MODE_TIMER ; 
 int /*<<< orphan*/  snd_ad1816a_close (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 struct snd_ad1816a* snd_timer_chip (struct snd_timer*) ; 

__attribute__((used)) static int snd_ad1816a_timer_close(struct snd_timer *timer)
{
	struct snd_ad1816a *chip = snd_timer_chip(timer);
	snd_ad1816a_close(chip, AD1816A_MODE_TIMER);
	return 0;
}