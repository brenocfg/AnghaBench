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
struct snd_efw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINT_MAX ; 
 int command_set_clock (struct snd_efw*,int /*<<< orphan*/ ,unsigned int) ; 

int snd_efw_command_set_sampling_rate(struct snd_efw *efw, unsigned int rate)
{
	return command_set_clock(efw, UINT_MAX, rate);
}