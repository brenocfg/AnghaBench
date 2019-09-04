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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
#define  QID_BEACON 129 
#define  QID_RX 128 
 int /*<<< orphan*/  TXRX_CSR0 ; 
 int /*<<< orphan*/  TXRX_CSR0_DISABLE_RX ; 
 int /*<<< orphan*/  TXRX_CSR9 ; 
 int /*<<< orphan*/  TXRX_CSR9_BEACON_GEN ; 
 int /*<<< orphan*/  TXRX_CSR9_TBTT_ENABLE ; 
 int /*<<< orphan*/  TXRX_CSR9_TSF_TICKING ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt61pci_start_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	switch (queue->qid) {
	case QID_RX:
		reg = rt2x00mmio_register_read(rt2x00dev, TXRX_CSR0);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
		rt2x00mmio_register_write(rt2x00dev, TXRX_CSR0, reg);
		break;
	case QID_BEACON:
		reg = rt2x00mmio_register_read(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
		rt2x00mmio_register_write(rt2x00dev, TXRX_CSR9, reg);
		break;
	default:
		break;
	}
}