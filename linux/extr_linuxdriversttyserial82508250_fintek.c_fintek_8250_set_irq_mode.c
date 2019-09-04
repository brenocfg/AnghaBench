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
struct fintek_8250 {int pid; int /*<<< orphan*/  index; } ;

/* Variables and functions */
#define  CHIP_ID_F81216 132 
#define  CHIP_ID_F81216AD 131 
#define  CHIP_ID_F81216H 130 
#define  CHIP_ID_F81865 129 
#define  CHIP_ID_F81866 128 
 int /*<<< orphan*/  F81866_FIFO_CTRL ; 
 int /*<<< orphan*/  F81866_IRQ_MODE ; 
 int /*<<< orphan*/  F81866_IRQ_MODE0 ; 
 int /*<<< orphan*/  F81866_IRQ_MODE1 ; 
 int /*<<< orphan*/  F81866_IRQ_SHARE ; 
 int /*<<< orphan*/  FINTEK_IRQ_MODE ; 
 int /*<<< orphan*/  IRQ_EDGE_HIGH ; 
 int /*<<< orphan*/  IRQ_LEVEL_LOW ; 
 int /*<<< orphan*/  IRQ_MODE_MASK ; 
 int /*<<< orphan*/  IRQ_SHARE ; 
 int /*<<< orphan*/  LDN ; 
 int /*<<< orphan*/  sio_write_mask_reg (struct fintek_8250*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_write_reg (struct fintek_8250*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fintek_8250_set_irq_mode(struct fintek_8250 *pdata, bool is_level)
{
	sio_write_reg(pdata, LDN, pdata->index);

	switch (pdata->pid) {
	case CHIP_ID_F81866:
		sio_write_mask_reg(pdata, F81866_FIFO_CTRL, F81866_IRQ_MODE1,
				   0);
		/* fall through */
	case CHIP_ID_F81865:
		sio_write_mask_reg(pdata, F81866_IRQ_MODE, F81866_IRQ_SHARE,
				   F81866_IRQ_SHARE);
		sio_write_mask_reg(pdata, F81866_IRQ_MODE, F81866_IRQ_MODE0,
				   is_level ? 0 : F81866_IRQ_MODE0);
		break;

	case CHIP_ID_F81216AD:
	case CHIP_ID_F81216H:
	case CHIP_ID_F81216:
		sio_write_mask_reg(pdata, FINTEK_IRQ_MODE, IRQ_SHARE,
				   IRQ_SHARE);
		sio_write_mask_reg(pdata, FINTEK_IRQ_MODE, IRQ_MODE_MASK,
				   is_level ? IRQ_LEVEL_LOW : IRQ_EDGE_HIGH);
		break;
	}
}