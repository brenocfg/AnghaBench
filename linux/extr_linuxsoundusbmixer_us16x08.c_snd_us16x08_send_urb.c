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
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_US16X08_URB_REQUEST ; 
 int /*<<< orphan*/  SND_US16X08_URB_REQUESTTYPE ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_us16x08_send_urb(struct snd_usb_audio *chip, char *buf, int size)
{
	return snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			SND_US16X08_URB_REQUEST, SND_US16X08_URB_REQUESTTYPE,
			0, 0, buf, size);
}