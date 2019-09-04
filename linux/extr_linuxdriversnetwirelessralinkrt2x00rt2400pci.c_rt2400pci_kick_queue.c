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
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_ATIM 128 
 int /*<<< orphan*/  TXCSR0 ; 
 int /*<<< orphan*/  TXCSR0_KICK_ATIM ; 
 int /*<<< orphan*/  TXCSR0_KICK_PRIO ; 
 int /*<<< orphan*/  TXCSR0_KICK_TX ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2400pci_kick_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	switch (queue->qid) {
	case QID_AC_VO:
		reg = rt2x00mmio_register_read(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_PRIO, 1);
		rt2x00mmio_register_write(rt2x00dev, TXCSR0, reg);
		break;
	case QID_AC_VI:
		reg = rt2x00mmio_register_read(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_TX, 1);
		rt2x00mmio_register_write(rt2x00dev, TXCSR0, reg);
		break;
	case QID_ATIM:
		reg = rt2x00mmio_register_read(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_ATIM, 1);
		rt2x00mmio_register_write(rt2x00dev, TXCSR0, reg);
		break;
	default:
		break;
	}
}