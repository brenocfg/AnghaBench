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
struct snd_usb_audio {int dummy; } ;
struct audioformat {int dummy; } ;

/* Variables and functions */
 int __snd_usb_add_audio_stream (struct snd_usb_audio*,int,struct audioformat*,int /*<<< orphan*/ *) ; 

int snd_usb_add_audio_stream(struct snd_usb_audio *chip,
			     int stream,
			     struct audioformat *fp)
{
	return __snd_usb_add_audio_stream(chip, stream, fp, NULL);
}