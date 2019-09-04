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
struct dasd_device {TYPE_1__* block; } ;
struct dasd_ccw_req {int /*<<< orphan*/  stopclk; int /*<<< orphan*/  status; struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bp_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_CLEAR_PENDING ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  mdsk_init_io (struct dasd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdsk_term_io (struct dasd_device*) ; 

__attribute__((used)) static int
dasd_diag_term_IO(struct dasd_ccw_req * cqr)
{
	struct dasd_device *device;

	device = cqr->startdev;
	mdsk_term_io(device);
	mdsk_init_io(device, device->block->bp_block, 0, NULL);
	cqr->status = DASD_CQR_CLEAR_PENDING;
	cqr->stopclk = get_tod_clock();
	dasd_schedule_device_bh(device);
	return 0;
}