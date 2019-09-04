#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct niu_bmac_stats {int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_2__ {struct niu_bmac_stats bmac; } ;
struct niu {TYPE_1__ mac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRXMAC_ALIGN_ERR_CNT ; 
 int /*<<< orphan*/  BRXMAC_CODE_VIOL_ERR_CNT ; 
 int /*<<< orphan*/  BRXMAC_FRAME_CNT ; 
 int /*<<< orphan*/  BTXMAC_BYTE_CNT ; 
 int /*<<< orphan*/  BTXMAC_FRM_CNT ; 
 scalar_t__ nr64_mac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_sync_bmac_stats(struct niu *np)
{
	struct niu_bmac_stats *mp = &np->mac_stats.bmac;

	mp->tx_bytes += nr64_mac(BTXMAC_BYTE_CNT);
	mp->tx_frames += nr64_mac(BTXMAC_FRM_CNT);

	mp->rx_frames += nr64_mac(BRXMAC_FRAME_CNT);
	mp->rx_align_errors += nr64_mac(BRXMAC_ALIGN_ERR_CNT);
	mp->rx_crc_errors += nr64_mac(BRXMAC_ALIGN_ERR_CNT);
	mp->rx_len_errors += nr64_mac(BRXMAC_CODE_VIOL_ERR_CNT);
}