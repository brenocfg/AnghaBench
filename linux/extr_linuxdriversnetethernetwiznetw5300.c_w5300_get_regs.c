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
typedef  int u16 ;
struct w5300_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;

/* Variables and functions */
 int W5300_REGS_LEN ; 
#define  W5300_S0_RX_FIFO 129 
#define  W5300_S0_TX_FIFO 128 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 int w5300_read (struct w5300_priv*,int) ; 

__attribute__((used)) static void w5300_get_regs(struct net_device *ndev,
			   struct ethtool_regs *regs, void *_buf)
{
	struct w5300_priv *priv = netdev_priv(ndev);
	u8 *buf = _buf;
	u16 addr;
	u16 data;

	regs->version = 1;
	for (addr = 0; addr < W5300_REGS_LEN; addr += 2) {
		switch (addr & 0x23f) {
		case W5300_S0_TX_FIFO: /* cannot read TX_FIFO */
		case W5300_S0_RX_FIFO: /* cannot read RX_FIFO */
			data = 0xffff;
			break;
		default:
			data = w5300_read(priv, addr);
			break;
		}
		*buf++ = data >> 8;
		*buf++ = data;
	}
}