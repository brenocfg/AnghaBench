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
struct dasd_ccw_req {int expires; scalar_t__ retries; int /*<<< orphan*/  flags; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  callback; } ;
struct dasd_block {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 int EAGAIN ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_add_request_head (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dasd_eckd_analysis_callback ; 
 struct dasd_ccw_req* dasd_eckd_analysis_ccw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_eckd_start_analysis(struct dasd_block *block)
{
	struct dasd_ccw_req *init_cqr;

	init_cqr = dasd_eckd_analysis_ccw(block->base);
	if (IS_ERR(init_cqr))
		return PTR_ERR(init_cqr);
	init_cqr->callback = dasd_eckd_analysis_callback;
	init_cqr->callback_data = NULL;
	init_cqr->expires = 5*HZ;
	/* first try without ERP, so we can later handle unformatted
	 * devices as special case
	 */
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &init_cqr->flags);
	init_cqr->retries = 0;
	dasd_add_request_head(init_cqr);
	return -EAGAIN;
}