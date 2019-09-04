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
struct snd_usb_caiaqdev {int /*<<< orphan*/  input_dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  MASCHINE_PAD (unsigned int) ; 
 unsigned int MASCHINE_PADS ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usb_caiaq_maschine_dispatch(struct snd_usb_caiaqdev *cdev,
					const unsigned char *buf,
					unsigned int len)
{
	unsigned int i, pad_id;
	__le16 *pressure = (__le16 *) buf;

	for (i = 0; i < MASCHINE_PADS; i++) {
		pad_id = le16_to_cpu(*pressure) >> 12;
		input_report_abs(cdev->input_dev, MASCHINE_PAD(pad_id),
				 le16_to_cpu(*pressure) & 0xfff);
		pressure++;
	}

	input_sync(cdev->input_dev);
}