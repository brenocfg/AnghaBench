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
typedef  void* u64 ;
typedef  void* u32 ;
struct switch_port_stats {void* rx_bytes; void* tx_bytes; } ;
struct switch_dev {int dummy; } ;
struct b53_mib_desc {int size; int /*<<< orphan*/  offset; } ;
struct b53_device {int enabled_ports; scalar_t__* buf; } ;

/* Variables and functions */
 int B53XX_MIB_RXB_ID ; 
 int B53XX_MIB_TXB_ID ; 
 int /*<<< orphan*/  B53_MIB_PAGE (int) ; 
 int B63XX_MIB_RXB_ID ; 
 int B63XX_MIB_TXB_ID ; 
 int BIT (int) ; 
 int EINVAL ; 
 struct b53_mib_desc* b53_mibs ; 
 struct b53_mib_desc* b53_mibs_63xx ; 
 struct b53_mib_desc* b53_mibs_65 ; 
 int /*<<< orphan*/  b53_read32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  b53_read64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 scalar_t__ is63xx (struct b53_device*) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_port_get_stats(struct switch_dev *sw_dev, int port,
				struct switch_port_stats *stats)
{
	struct b53_device *dev = sw_to_b53(sw_dev);
	const struct b53_mib_desc *mibs;
	int txb_id, rxb_id;
	u64 rxb, txb;

	if (!(BIT(port) & dev->enabled_ports))
		return -EINVAL;

	txb_id = B53XX_MIB_TXB_ID;
	rxb_id = B53XX_MIB_RXB_ID;

	if (is5365(dev)) {
		if (port == 5)
			port = 8;

		mibs = b53_mibs_65;
	} else if (is63xx(dev)) {
		mibs = b53_mibs_63xx;
		txb_id = B63XX_MIB_TXB_ID;
		rxb_id = B63XX_MIB_RXB_ID;
	} else {
		mibs = b53_mibs;
	}

	dev->buf[0] = 0;

	if (mibs->size == 8) {
		b53_read64(dev, B53_MIB_PAGE(port), mibs[txb_id].offset, &txb);
		b53_read64(dev, B53_MIB_PAGE(port), mibs[rxb_id].offset, &rxb);
	} else {
		u32 val32;

		b53_read32(dev, B53_MIB_PAGE(port), mibs[txb_id].offset, &val32);
		txb = val32;

		b53_read32(dev, B53_MIB_PAGE(port), mibs[rxb_id].offset, &val32);
		rxb = val32;
	}

	stats->tx_bytes = txb;
	stats->rx_bytes = rxb;

	return 0;
}