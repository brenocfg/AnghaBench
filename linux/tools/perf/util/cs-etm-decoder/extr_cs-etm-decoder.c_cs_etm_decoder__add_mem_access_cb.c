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
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_decoder {int /*<<< orphan*/  dcd_tree; int /*<<< orphan*/  mem_access; } ;
typedef  int /*<<< orphan*/  cs_etm_mem_cb_type ;

/* Variables and functions */
 int /*<<< orphan*/  OCSD_MEM_SPACE_ANY ; 
 int /*<<< orphan*/  cs_etm_decoder__mem_access ; 
 scalar_t__ ocsd_dt_add_callback_trcid_mem_acc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cs_etm_decoder*) ; 

int cs_etm_decoder__add_mem_access_cb(struct cs_etm_decoder *decoder,
				      u64 start, u64 end,
				      cs_etm_mem_cb_type cb_func)
{
	decoder->mem_access = cb_func;

	if (ocsd_dt_add_callback_trcid_mem_acc(decoder->dcd_tree, start, end,
					       OCSD_MEM_SPACE_ANY,
					       cs_etm_decoder__mem_access,
					       decoder))
		return -1;

	return 0;
}