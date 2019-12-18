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
struct snd_msnd {long play_sample_size; long play_sample_rate; long play_channels; } ;

/* Variables and functions */
 long HZ ; 

__attribute__((used)) static inline long get_play_delay_jiffies(struct snd_msnd *chip, long size)
{
	long tmp = (size * HZ * chip->play_sample_size) / 8;
	return tmp / (chip->play_sample_rate * chip->play_channels);
}