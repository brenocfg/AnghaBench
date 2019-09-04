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
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {int flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int FLAG_TOSHIBA_DELAY ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NCR5380_poll_politely (struct NCR5380_hostdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int NCR5380_read (int /*<<< orphan*/ ) ; 
 int SR_BSY ; 
 int /*<<< orphan*/  STATUS_REG ; 
 int /*<<< orphan*/  do_abort (struct Scsi_Host*) ; 
 int /*<<< orphan*/  do_reset (struct Scsi_Host*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int NCR5380_maybe_reset_bus(struct Scsi_Host *instance)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);
	int pass;

	for (pass = 1; (NCR5380_read(STATUS_REG) & SR_BSY) && pass <= 6; ++pass) {
		switch (pass) {
		case 1:
		case 3:
		case 5:
			shost_printk(KERN_ERR, instance, "SCSI bus busy, waiting up to five seconds\n");
			NCR5380_poll_politely(hostdata,
			                      STATUS_REG, SR_BSY, 0, 5 * HZ);
			break;
		case 2:
			shost_printk(KERN_ERR, instance, "bus busy, attempting abort\n");
			do_abort(instance);
			break;
		case 4:
			shost_printk(KERN_ERR, instance, "bus busy, attempting reset\n");
			do_reset(instance);
			/* Wait after a reset; the SCSI standard calls for
			 * 250ms, we wait 500ms to be on the safe side.
			 * But some Toshiba CD-ROMs need ten times that.
			 */
			if (hostdata->flags & FLAG_TOSHIBA_DELAY)
				msleep(2500);
			else
				msleep(500);
			break;
		case 6:
			shost_printk(KERN_ERR, instance, "bus locked solid\n");
			return -ENXIO;
		}
	}
	return 0;
}