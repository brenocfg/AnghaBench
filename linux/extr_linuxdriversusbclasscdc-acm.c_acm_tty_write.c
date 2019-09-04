#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct acm* driver_data; } ;
struct acm_wb {int len; int /*<<< orphan*/  urb; scalar_t__ use; int /*<<< orphan*/  buf; } ;
struct acm {int writesize; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  delayed; scalar_t__ susp_count; int /*<<< orphan*/  control; TYPE_1__* data; int /*<<< orphan*/  dev; struct acm_wb* wb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int acm_start_wb (struct acm*,struct acm_wb*) ; 
 int acm_wb_alloc (struct acm*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_anchor_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface_async (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acm_tty_write(struct tty_struct *tty,
					const unsigned char *buf, int count)
{
	struct acm *acm = tty->driver_data;
	int stat;
	unsigned long flags;
	int wbn;
	struct acm_wb *wb;

	if (!count)
		return 0;

	dev_vdbg(&acm->data->dev, "%d bytes from tty layer\n", count);

	spin_lock_irqsave(&acm->write_lock, flags);
	wbn = acm_wb_alloc(acm);
	if (wbn < 0) {
		spin_unlock_irqrestore(&acm->write_lock, flags);
		return 0;
	}
	wb = &acm->wb[wbn];

	if (!acm->dev) {
		wb->use = 0;
		spin_unlock_irqrestore(&acm->write_lock, flags);
		return -ENODEV;
	}

	count = (count > acm->writesize) ? acm->writesize : count;
	dev_vdbg(&acm->data->dev, "writing %d bytes\n", count);
	memcpy(wb->buf, buf, count);
	wb->len = count;

	stat = usb_autopm_get_interface_async(acm->control);
	if (stat) {
		wb->use = 0;
		spin_unlock_irqrestore(&acm->write_lock, flags);
		return stat;
	}

	if (acm->susp_count) {
		usb_anchor_urb(wb->urb, &acm->delayed);
		spin_unlock_irqrestore(&acm->write_lock, flags);
		return count;
	}

	stat = acm_start_wb(acm, wb);
	spin_unlock_irqrestore(&acm->write_lock, flags);

	if (stat < 0)
		return stat;
	return count;
}