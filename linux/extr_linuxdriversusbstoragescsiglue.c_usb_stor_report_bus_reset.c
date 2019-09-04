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
struct us_data {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_lock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_report_bus_reset (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unlock (struct Scsi_Host*) ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 

void usb_stor_report_bus_reset(struct us_data *us)
{
	struct Scsi_Host *host = us_to_host(us);

	scsi_lock(host);
	scsi_report_bus_reset(host, 0);
	scsi_unlock(host);
}