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
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int expires; int lpm; int retries; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/ * block; struct dasd_device* memdev; struct dasd_device* startdev; int /*<<< orphan*/  magic; struct ccw1* cpaddr; } ;
struct ccw1 {int /*<<< orphan*/  count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
typedef  int __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_VERIFY_PATH ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_RCD ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DASD_ECKD_RCD_DATA_SIZE ; 
 int HZ ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_fill_rcd_cqr(struct dasd_device *device,
				   struct dasd_ccw_req *cqr,
				   __u8 *rcd_buffer,
				   __u8 lpm)
{
	struct ccw1 *ccw;
	/*
	 * buffer has to start with EBCDIC "V1.0" to show
	 * support for virtual device SNEQ
	 */
	rcd_buffer[0] = 0xE5;
	rcd_buffer[1] = 0xF1;
	rcd_buffer[2] = 0x4B;
	rcd_buffer[3] = 0xF0;

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_RCD;
	ccw->flags = 0;
	ccw->cda = (__u32)(addr_t)rcd_buffer;
	ccw->count = DASD_ECKD_RCD_DATA_SIZE;
	cqr->magic = DASD_ECKD_MAGIC;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = NULL;
	cqr->expires = 10*HZ;
	cqr->lpm = lpm;
	cqr->retries = 256;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;
	set_bit(DASD_CQR_VERIFY_PATH, &cqr->flags);
}