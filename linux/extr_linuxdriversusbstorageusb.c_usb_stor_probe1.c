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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct us_unusual_dev {int dummy; } ;
struct us_data {int /*<<< orphan*/  scan_dwork; int /*<<< orphan*/  delay_wait; int /*<<< orphan*/  notify; int /*<<< orphan*/  cmnd_ready; int /*<<< orphan*/  dev_mutex; } ;
struct scsi_host_template {int dummy; } ;
struct Scsi_Host {int max_cmd_len; int /*<<< orphan*/  sg_tablesize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int associate_dev (struct us_data*,struct usb_interface*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int get_device_info (struct us_data*,struct usb_device_id const*,struct us_unusual_dev*) ; 
 int /*<<< orphan*/  get_protocol (struct us_data*) ; 
 int /*<<< orphan*/  get_transport (struct us_data*) ; 
 struct us_data* host_to_us (struct Scsi_Host*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_everything (struct us_data*) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  us_set_lock_class (int /*<<< orphan*/ *,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 
 int /*<<< orphan*/  usb_stor_scan_dwork ; 
 int /*<<< orphan*/  usb_stor_sg_tablesize (struct usb_interface*) ; 

int usb_stor_probe1(struct us_data **pus,
		struct usb_interface *intf,
		const struct usb_device_id *id,
		struct us_unusual_dev *unusual_dev,
		struct scsi_host_template *sht)
{
	struct Scsi_Host *host;
	struct us_data *us;
	int result;

	dev_info(&intf->dev, "USB Mass Storage device detected\n");

	/*
	 * Ask the SCSI layer to allocate a host structure, with extra
	 * space at the end for our private us_data structure.
	 */
	host = scsi_host_alloc(sht, sizeof(*us));
	if (!host) {
		dev_warn(&intf->dev, "Unable to allocate the scsi host\n");
		return -ENOMEM;
	}

	/*
	 * Allow 16-byte CDBs and thus > 2TB
	 */
	host->max_cmd_len = 16;
	host->sg_tablesize = usb_stor_sg_tablesize(intf);
	*pus = us = host_to_us(host);
	mutex_init(&(us->dev_mutex));
	us_set_lock_class(&us->dev_mutex, intf);
	init_completion(&us->cmnd_ready);
	init_completion(&(us->notify));
	init_waitqueue_head(&us->delay_wait);
	INIT_DELAYED_WORK(&us->scan_dwork, usb_stor_scan_dwork);

	/* Associate the us_data structure with the USB device */
	result = associate_dev(us, intf);
	if (result)
		goto BadDevice;

	/* Get the unusual_devs entries and the descriptors */
	result = get_device_info(us, id, unusual_dev);
	if (result)
		goto BadDevice;

	/* Get standard transport and protocol settings */
	get_transport(us);
	get_protocol(us);

	/*
	 * Give the caller a chance to fill in specialized transport
	 * or protocol settings.
	 */
	return 0;

BadDevice:
	usb_stor_dbg(us, "storage_probe() failed\n");
	release_everything(us);
	return result;
}