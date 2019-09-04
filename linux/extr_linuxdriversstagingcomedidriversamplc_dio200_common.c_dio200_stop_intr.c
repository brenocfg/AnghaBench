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
struct dio200_subdev_intr {int active; int /*<<< orphan*/  ofs; scalar_t__ enabled_isns; } ;
struct dio200_board {scalar_t__ has_int_sce; } ;
struct comedi_subdevice {struct dio200_subdev_intr* private; } ;
struct comedi_device {struct dio200_board* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dio200_stop_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	const struct dio200_board *board = dev->board_ptr;
	struct dio200_subdev_intr *subpriv = s->private;

	subpriv->active = false;
	subpriv->enabled_isns = 0;
	if (board->has_int_sce)
		dio200_write8(dev, subpriv->ofs, 0);
}