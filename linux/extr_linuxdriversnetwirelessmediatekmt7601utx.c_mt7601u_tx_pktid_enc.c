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
typedef  int u8 ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u8 mt7601u_tx_pktid_enc(struct mt7601u_dev *dev, u8 rate, bool is_probe)
{
	u8 encoded = (rate + 1) + is_probe *  8;

	/* Because PKT_ID 0 disables status reporting only 15 values are
	 * available but 16 are needed (8 MCS * 2 for encoding is_probe)
	 * - we need to cram together two rates. MCS0 and MCS7 with is_probe
	 * share PKT_ID 9.
	 */
	if (is_probe && rate == 7)
		return encoded - 7;

	return encoded;
}