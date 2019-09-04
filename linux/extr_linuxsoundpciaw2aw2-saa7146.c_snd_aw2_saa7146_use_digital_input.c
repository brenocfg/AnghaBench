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
struct snd_aw2_saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  WRITEREG (int,int /*<<< orphan*/ ) ; 

void snd_aw2_saa7146_use_digital_input(struct snd_aw2_saa7146 *chip,
				       int use_digital)
{
	/* FIXME: switch between analog and digital input does not always work.
	   It can produce a kind of white noise. It seams that received data
	   are inverted sometime (endian inversion). Why ? I don't know, maybe
	   a problem of synchronization... However for the time being I have
	   not found the problem. Workaround: switch again (and again) between
	   digital and analog input until it works. */
	if (use_digital)
		WRITEREG(0x40, GPIO_CTRL);
	else
		WRITEREG(0x50, GPIO_CTRL);
}