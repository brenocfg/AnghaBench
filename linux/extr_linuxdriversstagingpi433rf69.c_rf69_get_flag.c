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
struct spi_device {int dummy; } ;
typedef  enum flag { ____Placeholder_flag } flag ;

/* Variables and functions */
 int MASK_IRQFLAGS1_AUTOMODE ; 
 int MASK_IRQFLAGS1_MODE_READY ; 
 int MASK_IRQFLAGS1_PLL_LOCK ; 
 int MASK_IRQFLAGS1_RSSI ; 
 int MASK_IRQFLAGS1_RX_READY ; 
 int MASK_IRQFLAGS1_SYNC_ADDRESS_MATCH ; 
 int MASK_IRQFLAGS1_TIMEOUT ; 
 int MASK_IRQFLAGS1_TX_READY ; 
 int MASK_IRQFLAGS2_CRC_OK ; 
 int MASK_IRQFLAGS2_FIFO_FULL ; 
 int MASK_IRQFLAGS2_FIFO_LEVEL ; 
 int MASK_IRQFLAGS2_FIFO_NOT_EMPTY ; 
 int MASK_IRQFLAGS2_FIFO_OVERRUN ; 
 int MASK_IRQFLAGS2_LOW_BAT ; 
 int MASK_IRQFLAGS2_PACKET_SENT ; 
 int MASK_IRQFLAGS2_PAYLOAD_READY ; 
 int /*<<< orphan*/  REG_IRQFLAGS1 ; 
 int /*<<< orphan*/  REG_IRQFLAGS2 ; 
#define  automode 143 
#define  battery_low 142 
#define  crc_ok 141 
#define  fifo_empty 140 
#define  fifo_full 139 
#define  fifo_level_below_threshold 138 
#define  fifo_overrun 137 
#define  mode_switch_completed 136 
#define  packet_sent 135 
#define  payload_ready 134 
#define  pll_locked 133 
#define  ready_to_receive 132 
#define  ready_to_send 131 
 int rf69_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 
#define  rssi_exceeded_threshold 130 
#define  sync_address_match 129 
#define  timeout 128 

bool rf69_get_flag(struct spi_device *spi, enum flag flag)
{
	switch (flag) {
	case mode_switch_completed:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_MODE_READY);
	case ready_to_receive:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_RX_READY);
	case ready_to_send:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_TX_READY);
	case pll_locked:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_PLL_LOCK);
	case rssi_exceeded_threshold:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_RSSI);
	case timeout:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_TIMEOUT);
	case automode:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_AUTOMODE);
	case sync_address_match:
		return (rf69_read_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_SYNC_ADDRESS_MATCH);
	case fifo_full:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_FULL);
/*
 *	case fifo_not_empty:
 *		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_NOT_EMPTY);
 */
	case fifo_empty:
		return !(rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_NOT_EMPTY);
	case fifo_level_below_threshold:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_LEVEL);
	case fifo_overrun:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_OVERRUN);
	case packet_sent:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_PACKET_SENT);
	case payload_ready:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_PAYLOAD_READY);
	case crc_ok:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_CRC_OK);
	case battery_low:
		return (rf69_read_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_LOW_BAT);
	default:			 return false;
	}
}