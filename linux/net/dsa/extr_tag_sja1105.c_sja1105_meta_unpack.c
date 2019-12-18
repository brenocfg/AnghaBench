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
struct sk_buff {int dummy; } ;
struct sja1105_meta {int /*<<< orphan*/  switch_id; int /*<<< orphan*/  source_port; int /*<<< orphan*/  dmac_byte_3; int /*<<< orphan*/  dmac_byte_4; int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  UNPACK ; 
 int /*<<< orphan*/  packing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff const*) ; 

__attribute__((used)) static void sja1105_meta_unpack(const struct sk_buff *skb,
				struct sja1105_meta *meta)
{
	u8 *buf = skb_mac_header(skb) + ETH_HLEN;

	/* UM10944.pdf section 4.2.17 AVB Parameters:
	 * Structure of the meta-data follow-up frame.
	 * It is in network byte order, so there are no quirks
	 * while unpacking the meta frame.
	 *
	 * Also SJA1105 E/T only populates bits 23:0 of the timestamp
	 * whereas P/Q/R/S does 32 bits. Since the structure is the
	 * same and the E/T puts zeroes in the high-order byte, use
	 * a unified unpacking command for both device series.
	 */
	packing(buf,     &meta->tstamp,     31, 0, 4, UNPACK, 0);
	packing(buf + 4, &meta->dmac_byte_4, 7, 0, 1, UNPACK, 0);
	packing(buf + 5, &meta->dmac_byte_3, 7, 0, 1, UNPACK, 0);
	packing(buf + 6, &meta->source_port, 7, 0, 1, UNPACK, 0);
	packing(buf + 7, &meta->switch_id,   7, 0, 1, UNPACK, 0);
}