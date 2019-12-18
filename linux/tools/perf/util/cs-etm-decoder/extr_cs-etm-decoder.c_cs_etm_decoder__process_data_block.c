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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct cs_etm_decoder {int /*<<< orphan*/  prev_return; int /*<<< orphan*/  dcd_tree; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OCSD_DATA_RESP_IS_CONT (int /*<<< orphan*/ ) ; 
 scalar_t__ OCSD_DATA_RESP_IS_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSD_OP_DATA ; 
 int /*<<< orphan*/  OCSD_OP_FLUSH ; 
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  ocsd_dt_process_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/  const*,scalar_t__*) ; 

int cs_etm_decoder__process_data_block(struct cs_etm_decoder *decoder,
				       u64 indx, const u8 *buf,
				       size_t len, size_t *consumed)
{
	int ret = 0;
	ocsd_datapath_resp_t cur = OCSD_RESP_CONT;
	ocsd_datapath_resp_t prev_return = decoder->prev_return;
	size_t processed = 0;
	u32 count;

	while (processed < len) {
		if (OCSD_DATA_RESP_IS_WAIT(prev_return)) {
			cur = ocsd_dt_process_data(decoder->dcd_tree,
						   OCSD_OP_FLUSH,
						   0,
						   0,
						   NULL,
						   NULL);
		} else if (OCSD_DATA_RESP_IS_CONT(prev_return)) {
			cur = ocsd_dt_process_data(decoder->dcd_tree,
						   OCSD_OP_DATA,
						   indx + processed,
						   len - processed,
						   &buf[processed],
						   &count);
			processed += count;
		} else {
			ret = -EINVAL;
			break;
		}

		/*
		 * Return to the input code if the packet buffer is full.
		 * Flushing will get done once the packet buffer has been
		 * processed.
		 */
		if (OCSD_DATA_RESP_IS_WAIT(cur))
			break;

		prev_return = cur;
	}

	decoder->prev_return = cur;
	*consumed = processed;

	return ret;
}