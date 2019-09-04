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
typedef  int u32 ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int BRCMF_BT_SCO_SAMPLES ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int brcmf_btcoex_params_read (struct brcmf_if*,int,int*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 

__attribute__((used)) static bool brcmf_btcoex_is_sco_active(struct brcmf_if *ifp)
{
	int ioc_res = 0;
	bool res = false;
	int sco_id_cnt = 0;
	u32 param27;
	int i;

	for (i = 0; i < BRCMF_BT_SCO_SAMPLES; i++) {
		ioc_res = brcmf_btcoex_params_read(ifp, 27, &param27);

		if (ioc_res < 0) {
			brcmf_err("ioc read btc params error\n");
			break;
		}

		brcmf_dbg(INFO, "sample[%d], btc_params 27:%x\n", i, param27);

		if ((param27 & 0x6) == 2) { /* count both sco & esco  */
			sco_id_cnt++;
		}

		if (sco_id_cnt > 2) {
			brcmf_dbg(INFO,
				  "sco/esco detected, pkt id_cnt:%d samples:%d\n",
				  sco_id_cnt, i);
			res = true;
			break;
		}
	}
	brcmf_dbg(TRACE, "exit: result=%d\n", res);
	return res;
}