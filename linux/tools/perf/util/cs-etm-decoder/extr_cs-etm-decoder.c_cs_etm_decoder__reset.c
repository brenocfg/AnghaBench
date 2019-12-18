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
struct cs_etm_decoder {int /*<<< orphan*/  dcd_tree; int /*<<< orphan*/  prev_return; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 scalar_t__ OCSD_DATA_RESP_IS_FATAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSD_OP_RESET ; 
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  ocsd_dt_process_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cs_etm_decoder__reset(struct cs_etm_decoder *decoder)
{
	ocsd_datapath_resp_t dp_ret;

	decoder->prev_return = OCSD_RESP_CONT;

	dp_ret = ocsd_dt_process_data(decoder->dcd_tree, OCSD_OP_RESET,
				      0, 0, NULL, NULL);
	if (OCSD_DATA_RESP_IS_FATAL(dp_ret))
		return -1;

	return 0;
}