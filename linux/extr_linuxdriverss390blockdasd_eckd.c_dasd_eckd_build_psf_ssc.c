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
struct dasd_psf_ssc_data {int suborder; int* reserved; int /*<<< orphan*/  order; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int retries; int expires; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/ * block; struct dasd_device* memdev; struct dasd_device* startdev; struct ccw1* cpaddr; scalar_t__ data; } ;
struct ccw1 {int count; scalar_t__ cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_PSF ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  PSF_ORDER_SSC ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tod_clock () ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_eckd_build_psf_ssc(struct dasd_device *device,
						    int enable_pav)
{
	struct dasd_ccw_req *cqr;
	struct dasd_psf_ssc_data *psf_ssc_data;
	struct ccw1 *ccw;

	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1 /* PSF */ ,
				  sizeof(struct dasd_psf_ssc_data),
				   device, NULL);

	if (IS_ERR(cqr)) {
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			   "Could not allocate PSF-SSC request");
		return cqr;
	}
	psf_ssc_data = (struct dasd_psf_ssc_data *)cqr->data;
	psf_ssc_data->order = PSF_ORDER_SSC;
	psf_ssc_data->suborder = 0xc0;
	if (enable_pav) {
		psf_ssc_data->suborder |= 0x08;
		psf_ssc_data->reserved[0] = 0x88;
	}
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->cda = (__u32)(addr_t)psf_ssc_data;
	ccw->count = 66;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = NULL;
	cqr->retries = 256;
	cqr->expires = 10*HZ;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;
	return cqr;
}