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
struct usbtmc_file_data {int eom_val; int /*<<< orphan*/  file_elem; int /*<<< orphan*/  term_char_enabled; int /*<<< orphan*/  term_char; int /*<<< orphan*/  timeout; struct usbtmc_device_data* data; } ;
struct usbtmc_device_data {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  file_list; int /*<<< orphan*/  TermCharEnabled; int /*<<< orphan*/  TermChar; int /*<<< orphan*/  kref; } ;
struct usb_interface {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct usbtmc_file_data* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBTMC_TIMEOUT ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct usbtmc_file_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usbtmc_device_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbtmc_driver ; 

__attribute__((used)) static int usbtmc_open(struct inode *inode, struct file *filp)
{
	struct usb_interface *intf;
	struct usbtmc_device_data *data;
	struct usbtmc_file_data *file_data;

	intf = usb_find_interface(&usbtmc_driver, iminor(inode));
	if (!intf) {
		pr_err("can not find device for minor %d", iminor(inode));
		return -ENODEV;
	}

	file_data = kzalloc(sizeof(*file_data), GFP_KERNEL);
	if (!file_data)
		return -ENOMEM;

	data = usb_get_intfdata(intf);
	/* Protect reference to data from file structure until release */
	kref_get(&data->kref);

	mutex_lock(&data->io_mutex);
	file_data->data = data;

	/* copy default values from device settings */
	file_data->timeout = USBTMC_TIMEOUT;
	file_data->term_char = data->TermChar;
	file_data->term_char_enabled = data->TermCharEnabled;
	file_data->eom_val = 1;

	INIT_LIST_HEAD(&file_data->file_elem);
	spin_lock_irq(&data->dev_lock);
	list_add_tail(&file_data->file_elem, &data->file_list);
	spin_unlock_irq(&data->dev_lock);
	mutex_unlock(&data->io_mutex);

	/* Store pointer in file structure's private data field */
	filp->private_data = file_data;

	return 0;
}