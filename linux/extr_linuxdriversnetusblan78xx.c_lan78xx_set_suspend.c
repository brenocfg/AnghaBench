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
typedef  int u32 ;
typedef  int u16 ;
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_RX ; 
 int MAC_RX_RXEN_ ; 
 int /*<<< orphan*/  MAC_TX ; 
 int MAC_TX_TXEN_ ; 
 int NUM_OF_WUF_CFG ; 
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_PHY_WAKE_EN_ ; 
 int PMT_CTL_RES_CLR_WKP_EN_ ; 
 int PMT_CTL_RES_CLR_WKP_STS_ ; 
 int PMT_CTL_SUS_MODE_0_ ; 
 int PMT_CTL_SUS_MODE_3_ ; 
 int PMT_CTL_SUS_MODE_MASK_ ; 
 int PMT_CTL_WOL_EN_ ; 
 int PMT_CTL_WUPS_MASK_ ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  WK_SRC ; 
 int /*<<< orphan*/  WUCSR ; 
 int /*<<< orphan*/  WUCSR2 ; 
 int WUCSR_BCST_EN_ ; 
 int WUCSR_MPEN_ ; 
 int WUCSR_PFDA_EN_ ; 
 int WUCSR_WAKE_EN_ ; 
 int /*<<< orphan*/  WUF_CFG (int) ; 
 int WUF_CFGX_CRC16_MASK_ ; 
 int WUF_CFGX_EN_ ; 
 int WUF_CFGX_OFFSET_SHIFT_ ; 
 int WUF_CFGX_TYPE_ALL_ ; 
 int WUF_CFGX_TYPE_MCAST_ ; 
 int /*<<< orphan*/  WUF_MASK0 (int) ; 
 int /*<<< orphan*/  WUF_MASK1 (int) ; 
 int /*<<< orphan*/  WUF_MASK2 (int) ; 
 int /*<<< orphan*/  WUF_MASK3 (int) ; 
 int hweight_long (unsigned long) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_wakeframe_crc16 (int const*,int) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan78xx_set_suspend(struct lan78xx_net *dev, u32 wol)
{
	u32 buf;
	int ret;
	int mask_index;
	u16 crc;
	u32 temp_wucsr;
	u32 temp_pmt_ctl;
	const u8 ipv4_multicast[3] = { 0x01, 0x00, 0x5E };
	const u8 ipv6_multicast[3] = { 0x33, 0x33 };
	const u8 arp_type[2] = { 0x08, 0x06 };

	ret = lan78xx_read_reg(dev, MAC_TX, &buf);
	buf &= ~MAC_TX_TXEN_;
	ret = lan78xx_write_reg(dev, MAC_TX, buf);
	ret = lan78xx_read_reg(dev, MAC_RX, &buf);
	buf &= ~MAC_RX_RXEN_;
	ret = lan78xx_write_reg(dev, MAC_RX, buf);

	ret = lan78xx_write_reg(dev, WUCSR, 0);
	ret = lan78xx_write_reg(dev, WUCSR2, 0);
	ret = lan78xx_write_reg(dev, WK_SRC, 0xFFF1FF1FUL);

	temp_wucsr = 0;

	temp_pmt_ctl = 0;
	ret = lan78xx_read_reg(dev, PMT_CTL, &temp_pmt_ctl);
	temp_pmt_ctl &= ~PMT_CTL_RES_CLR_WKP_EN_;
	temp_pmt_ctl |= PMT_CTL_RES_CLR_WKP_STS_;

	for (mask_index = 0; mask_index < NUM_OF_WUF_CFG; mask_index++)
		ret = lan78xx_write_reg(dev, WUF_CFG(mask_index), 0);

	mask_index = 0;
	if (wol & WAKE_PHY) {
		temp_pmt_ctl |= PMT_CTL_PHY_WAKE_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}
	if (wol & WAKE_MAGIC) {
		temp_wucsr |= WUCSR_MPEN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_3_;
	}
	if (wol & WAKE_BCAST) {
		temp_wucsr |= WUCSR_BCST_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}
	if (wol & WAKE_MCAST) {
		temp_wucsr |= WUCSR_WAKE_EN_;

		/* set WUF_CFG & WUF_MASK for IPv4 Multicast */
		crc = lan78xx_wakeframe_crc16(ipv4_multicast, 3);
		ret = lan78xx_write_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_MCAST_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		ret = lan78xx_write_reg(dev, WUF_MASK0(mask_index), 7);
		ret = lan78xx_write_reg(dev, WUF_MASK1(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK2(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		/* for IPv6 Multicast */
		crc = lan78xx_wakeframe_crc16(ipv6_multicast, 2);
		ret = lan78xx_write_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_MCAST_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		ret = lan78xx_write_reg(dev, WUF_MASK0(mask_index), 3);
		ret = lan78xx_write_reg(dev, WUF_MASK1(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK2(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}
	if (wol & WAKE_UCAST) {
		temp_wucsr |= WUCSR_PFDA_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}
	if (wol & WAKE_ARP) {
		temp_wucsr |= WUCSR_WAKE_EN_;

		/* set WUF_CFG & WUF_MASK
		 * for packettype (offset 12,13) = ARP (0x0806)
		 */
		crc = lan78xx_wakeframe_crc16(arp_type, 2);
		ret = lan78xx_write_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_ALL_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		ret = lan78xx_write_reg(dev, WUF_MASK0(mask_index), 0x3000);
		ret = lan78xx_write_reg(dev, WUF_MASK1(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK2(mask_index), 0);
		ret = lan78xx_write_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}

	ret = lan78xx_write_reg(dev, WUCSR, temp_wucsr);

	/* when multiple WOL bits are set */
	if (hweight_long((unsigned long)wol) > 1) {
		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	}
	ret = lan78xx_write_reg(dev, PMT_CTL, temp_pmt_ctl);

	/* clear WUPS */
	ret = lan78xx_read_reg(dev, PMT_CTL, &buf);
	buf |= PMT_CTL_WUPS_MASK_;
	ret = lan78xx_write_reg(dev, PMT_CTL, buf);

	ret = lan78xx_read_reg(dev, MAC_RX, &buf);
	buf |= MAC_RX_RXEN_;
	ret = lan78xx_write_reg(dev, MAC_RX, buf);

	return 0;
}