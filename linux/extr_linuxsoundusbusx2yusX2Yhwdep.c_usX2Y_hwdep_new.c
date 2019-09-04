#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int devnum; TYPE_2__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll; int /*<<< orphan*/  mmap; int /*<<< orphan*/  dsp_load; int /*<<< orphan*/  dsp_status; } ;
struct snd_hwdep {int exclusive; int /*<<< orphan*/  name; TYPE_1__ ops; int /*<<< orphan*/  private_data; int /*<<< orphan*/  iface; } ;
struct snd_card {int dummy; } ;
struct TYPE_4__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_USX2Y ; 
 int /*<<< orphan*/  SND_USX2Y_LOADER_ID ; 
 int snd_hwdep_new (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  snd_us428ctls_mmap ; 
 int /*<<< orphan*/  snd_us428ctls_poll ; 
 int /*<<< orphan*/  snd_usX2Y_hwdep_dsp_load ; 
 int /*<<< orphan*/  snd_usX2Y_hwdep_dsp_status ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  usX2Y (struct snd_card*) ; 

int usX2Y_hwdep_new(struct snd_card *card, struct usb_device* device)
{
	int err;
	struct snd_hwdep *hw;

	if ((err = snd_hwdep_new(card, SND_USX2Y_LOADER_ID, 0, &hw)) < 0)
		return err;

	hw->iface = SNDRV_HWDEP_IFACE_USX2Y;
	hw->private_data = usX2Y(card);
	hw->ops.dsp_status = snd_usX2Y_hwdep_dsp_status;
	hw->ops.dsp_load = snd_usX2Y_hwdep_dsp_load;
	hw->ops.mmap = snd_us428ctls_mmap;
	hw->ops.poll = snd_us428ctls_poll;
	hw->exclusive = 1;
	sprintf(hw->name, "/dev/bus/usb/%03d/%03d", device->bus->busnum, device->devnum);
	return 0;
}