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
typedef  int u8 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  set_samplerate_seq ;
typedef  int /*<<< orphan*/  poll_ready_seq ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MICROBOOK_BUF_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_usb_motu_microbookii_communicate (struct usb_device*,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int snd_usb_motu_microbookii_boot_quirk(struct usb_device *dev)
{
	int err, actual_length, poll_attempts = 0;
	static const u8 set_samplerate_seq[] = { 0x00, 0x00, 0x00, 0x00,
						 0x00, 0x00, 0x0b, 0x14,
						 0x00, 0x00, 0x00, 0x01 };
	static const u8 poll_ready_seq[] = { 0x00, 0x04, 0x00, 0x00,
					     0x00, 0x00, 0x0b, 0x18 };
	u8 *buf = kzalloc(MICROBOOK_BUF_SIZE, GFP_KERNEL);

	if (!buf)
		return -ENOMEM;

	dev_info(&dev->dev, "Waiting for MOTU Microbook II to boot up...\n");

	/* First we tell the device which sample rate to use. */
	memcpy(buf, set_samplerate_seq, sizeof(set_samplerate_seq));
	actual_length = sizeof(set_samplerate_seq);
	err = snd_usb_motu_microbookii_communicate(dev, buf, MICROBOOK_BUF_SIZE,
						   &actual_length);

	if (err < 0) {
		dev_err(&dev->dev,
			"failed setting the sample rate for Motu MicroBook II: %d\n",
			err);
		goto free_buf;
	}

	/* Then we poll every 100 ms until the device informs of its readiness. */
	while (true) {
		if (++poll_attempts > 100) {
			dev_err(&dev->dev,
				"failed booting Motu MicroBook II: timeout\n");
			err = -ENODEV;
			goto free_buf;
		}

		memset(buf, 0, MICROBOOK_BUF_SIZE);
		memcpy(buf, poll_ready_seq, sizeof(poll_ready_seq));

		actual_length = sizeof(poll_ready_seq);
		err = snd_usb_motu_microbookii_communicate(
			dev, buf, MICROBOOK_BUF_SIZE, &actual_length);
		if (err < 0) {
			dev_err(&dev->dev,
				"failed booting Motu MicroBook II: communication error %d\n",
				err);
			goto free_buf;
		}

		/* the device signals its readiness through a message of the
		 * form
		 *           XX 06 00 00 00 00 0b 18  00 00 00 01
		 * If the device is not yet ready to accept audio data, the
		 * last byte of that sequence is 00.
		 */
		if (actual_length == 12 && buf[actual_length - 1] == 1)
			break;

		msleep(100);
	}

	dev_info(&dev->dev, "MOTU MicroBook II ready\n");

free_buf:
	kfree(buf);
	return err;
}