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
struct das800_board {int name; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  spinlock; struct das800_board* board_ptr; } ;

/* Variables and functions */
 int BOARD_CIODAS800 ; 
 int BOARD_CIODAS801 ; 
 int BOARD_CIODAS802 ; 
 int BOARD_CIODAS80216 ; 
 int BOARD_DAS800 ; 
 int BOARD_DAS801 ; 
 int BOARD_DAS802 ; 
 int EINVAL ; 
 int /*<<< orphan*/  ID ; 
 struct das800_board const* das800_boards ; 
 int das800_ind_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static const struct das800_board *das800_probe(struct comedi_device *dev)
{
	const struct das800_board *board = dev->board_ptr;
	int index = board ? board - das800_boards : -EINVAL;
	int id_bits;
	unsigned long irq_flags;

	/*
	 * The dev->board_ptr will be set by comedi_device_attach() if the
	 * board name provided by the user matches a board->name in this
	 * driver. If so, this function sanity checks the id_bits to verify
	 * that the board is correct.
	 *
	 * If the dev->board_ptr is not set, the user is trying to attach
	 * an unspecified board to this driver. In this case the id_bits
	 * are used to 'probe' for the correct dev->board_ptr.
	 */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	id_bits = das800_ind_read(dev, ID) & 0x3;
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	switch (id_bits) {
	case 0x0:
		if (index == BOARD_DAS800 || index == BOARD_CIODAS800)
			return board;
		index = BOARD_DAS800;
		break;
	case 0x2:
		if (index == BOARD_DAS801 || index == BOARD_CIODAS801)
			return board;
		index = BOARD_DAS801;
		break;
	case 0x3:
		if (index == BOARD_DAS802 || index == BOARD_CIODAS802 ||
		    index == BOARD_CIODAS80216)
			return board;
		index = BOARD_DAS802;
		break;
	default:
		dev_dbg(dev->class_dev, "Board model: 0x%x (unknown)\n",
			id_bits);
		return NULL;
	}
	dev_dbg(dev->class_dev, "Board model (probed): %s series\n",
		das800_boards[index].name);

	return &das800_boards[index];
}