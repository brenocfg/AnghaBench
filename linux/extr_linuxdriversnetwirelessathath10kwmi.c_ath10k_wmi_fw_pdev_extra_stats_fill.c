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
struct ath10k_fw_stats_pdev {int /*<<< orphan*/  mib_int_count; int /*<<< orphan*/  no_beacons; int /*<<< orphan*/  fcs_bad; int /*<<< orphan*/  rts_good; int /*<<< orphan*/  rts_bad; } ;

/* Variables and functions */
 int ATH10K_FW_STATS_BUF_SIZE ; 
 int scnprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
ath10k_wmi_fw_pdev_extra_stats_fill(const struct ath10k_fw_stats_pdev *pdev,
				    char *buf, u32 *length)
{
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnprintf(buf + len, buf_len - len, "%30s %10u\n",
			"RTS bad count", pdev->rts_bad);
	len += scnprintf(buf + len, buf_len - len, "%30s %10u\n",
			"RTS good count", pdev->rts_good);
	len += scnprintf(buf + len, buf_len - len, "%30s %10u\n",
			"FCS bad count", pdev->fcs_bad);
	len += scnprintf(buf + len, buf_len - len, "%30s %10u\n",
			"No beacon count", pdev->no_beacons);
	len += scnprintf(buf + len, buf_len - len, "%30s %10u\n",
			"MIB int count", pdev->mib_int_count);

	len += scnprintf(buf + len, buf_len - len, "\n");
	*length = len;
}