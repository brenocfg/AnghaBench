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
struct snd_usb_audio {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_US16X08_URB_METER_REQUEST ; 
 int /*<<< orphan*/  SND_US16X08_URB_METER_REQUESTTYPE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_us16x08_recv_urb(struct snd_usb_audio *chip,
	unsigned char *buf, int size)
{

	mutex_lock(&chip->mutex);
	snd_usb_ctl_msg(chip->dev,
		usb_rcvctrlpipe(chip->dev, 0),
		SND_US16X08_URB_METER_REQUEST,
		SND_US16X08_URB_METER_REQUESTTYPE, 0, 0, buf, size);
	mutex_unlock(&chip->mutex);
	return 0;
}