#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  info1; } ;
struct TYPE_4__ {TYPE_1__ qca99x0; } ;
struct htt_rx_desc {TYPE_2__ msdu_end; } ;

/* Variables and functions */
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_MSDU_END_INFO1_L3_HDR_PAD ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_qca99x0_rx_desc_get_l3_pad_bytes(struct htt_rx_desc *rxd)
{
	return MS(__le32_to_cpu(rxd->msdu_end.qca99x0.info1),
		  RX_MSDU_END_INFO1_L3_HDR_PAD);
}