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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int DAX_CCB_RETRIES ; 
 int /*<<< orphan*/  DAX_CCB_USEC ; 
 int EAGAIN ; 
 unsigned long HV_EOK ; 
 int /*<<< orphan*/  dax_dbg (char*,char*,...) ; 
 char* dax_hv_errno (unsigned long,int*) ; 
 int /*<<< orphan*/  dax_info_dbg (char*,int,...) ; 
 unsigned long sun4v_ccb_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dax_ccb_kill(u64 ca, u16 *kill_res)
{
	unsigned long hv_ret;
	int count, ret = 0;
	char *err_str;

	for (count = 0; count < DAX_CCB_RETRIES; count++) {
		dax_dbg("attempting kill on ca_ra 0x%llx", ca);
		hv_ret = sun4v_ccb_kill(ca, kill_res);

		if (hv_ret == HV_EOK) {
			dax_info_dbg("HV_EOK (ca_ra 0x%llx): %d", ca,
				     *kill_res);
		} else {
			err_str = dax_hv_errno(hv_ret, &ret);
			dax_dbg("%s (ca_ra 0x%llx)", err_str, ca);
		}

		if (ret != -EAGAIN)
			return ret;
		dax_info_dbg("ccb_kill count = %d", count);
		udelay(DAX_CCB_USEC);
	}

	return -EAGAIN;
}