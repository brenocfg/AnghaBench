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
struct usb_line6_pod {int device_id; } ;
struct snd_card {struct usb_line6_pod* private_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct snd_card* dev_to_snd_card (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t device_id_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct snd_card *card = dev_to_snd_card(dev);
	struct usb_line6_pod *pod = card->private_data;

	return sprintf(buf, "%d\n", pod->device_id);
}