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
struct zoran {int dummy; } ;
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 unsigned int BT819_FIFO_RESET_HIGH ; 
 unsigned int BT819_FIFO_RESET_LOW ; 
 int /*<<< orphan*/  GPIO (struct zoran*,int,int) ; 
 struct zoran* to_zoran (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zoran_subdev_notify(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct zoran *zr = to_zoran(sd->v4l2_dev);

	/* Bt819 needs to reset its FIFO buffer using #FRST pin and
	   LML33 card uses GPIO(7) for that. */
	if (cmd == BT819_FIFO_RESET_LOW)
		GPIO(zr, 7, 0);
	else if (cmd == BT819_FIFO_RESET_HIGH)
		GPIO(zr, 7, 1);
}