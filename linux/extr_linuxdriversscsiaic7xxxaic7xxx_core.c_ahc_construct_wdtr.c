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
typedef  int /*<<< orphan*/  u_int ;
struct ahc_softc {int msgout_len; scalar_t__ msgout_index; scalar_t__ msgout_buf; } ;
struct ahc_devinfo {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_name (struct ahc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_populate_width_msg (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_construct_wdtr(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		   u_int bus_width)
{
	ahc->msgout_index += spi_populate_width_msg(
			ahc->msgout_buf + ahc->msgout_index, bus_width);
	ahc->msgout_len += 4;
	if (bootverbose) {
		printk("(%s:%c:%d:%d): Sending WDTR %x\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       devinfo->lun, bus_width);
	}
}