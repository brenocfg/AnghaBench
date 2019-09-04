#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irb {int /*<<< orphan*/  scsw; } ;
struct TYPE_6__ {int blksize; int stop_unit; int start_unit; } ;
struct format_check_t {TYPE_3__ expect; } ;
struct eckd_count {int dummy; } ;
struct TYPE_4__ {int* feature; } ;
struct TYPE_5__ {int trk_per_cyl; } ;
struct dasd_eckd_private {int fcx_max_data; TYPE_1__ features; TYPE_2__ rdc_data; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  dasd_eckd_format_evaluate_tracks (struct eckd_count*,struct format_check_t*,int,int,int,int) ; 
 int dasd_eckd_format_process_data (struct dasd_device*,TYPE_3__*,int,int,struct eckd_count*,int,struct irb*) ; 
 int /*<<< orphan*/  kfree (struct eckd_count*) ; 
 struct eckd_count* kzalloc (int,int) ; 
 int recs_per_track (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_eckd_check_device_format(struct dasd_device *base,
					 struct format_check_t *cdata,
					 int enable_pav)
{
	struct dasd_eckd_private *private = base->private;
	struct eckd_count *fmt_buffer;
	struct irb irb;
	int rpt_max, rpt_exp;
	int fmt_buffer_size;
	int trk_per_cyl;
	int trkcount;
	int tpm = 0;
	int rc;

	trk_per_cyl = private->rdc_data.trk_per_cyl;

	/* Get maximum and expected amount of records per track */
	rpt_max = recs_per_track(&private->rdc_data, 0, 512) + 1;
	rpt_exp = recs_per_track(&private->rdc_data, 0, cdata->expect.blksize);

	trkcount = cdata->expect.stop_unit - cdata->expect.start_unit + 1;
	fmt_buffer_size = trkcount * rpt_max * sizeof(struct eckd_count);

	fmt_buffer = kzalloc(fmt_buffer_size, GFP_KERNEL | GFP_DMA);
	if (!fmt_buffer)
		return -ENOMEM;

	/*
	 * A certain FICON feature subset is needed to operate in transport
	 * mode. Additionally, the support for transport mode is implicitly
	 * checked by comparing the buffer size with fcx_max_data. As long as
	 * the buffer size is smaller we can operate in transport mode and
	 * process multiple tracks. If not, only one track at once is being
	 * processed using command mode.
	 */
	if ((private->features.feature[40] & 0x04) &&
	    fmt_buffer_size <= private->fcx_max_data)
		tpm = 1;

	rc = dasd_eckd_format_process_data(base, &cdata->expect, enable_pav,
					   tpm, fmt_buffer, rpt_max, &irb);
	if (rc && rc != -EIO)
		goto out;
	if (rc == -EIO) {
		/*
		 * If our first attempt with transport mode enabled comes back
		 * with an incorrect length error, we're going to retry the
		 * check with command mode.
		 */
		if (tpm && scsw_cstat(&irb.scsw) == 0x40) {
			tpm = 0;
			rc = dasd_eckd_format_process_data(base, &cdata->expect,
							   enable_pav, tpm,
							   fmt_buffer, rpt_max,
							   &irb);
			if (rc)
				goto out;
		} else {
			goto out;
		}
	}

	dasd_eckd_format_evaluate_tracks(fmt_buffer, cdata, rpt_max, rpt_exp,
					 trk_per_cyl, tpm);

out:
	kfree(fmt_buffer);

	return rc;
}