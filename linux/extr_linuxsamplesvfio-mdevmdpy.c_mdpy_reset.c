#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mdev_state {TYPE_1__* type; scalar_t__ memblk; } ;
struct mdev_device {int dummy; } ;
struct TYPE_2__ {int width; int bytepp; int height; } ;

/* Variables and functions */
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

__attribute__((used)) static int mdpy_reset(struct mdev_device *mdev)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);
	u32 stride, i;

	/* initialize with gray gradient */
	stride = mdev_state->type->width * mdev_state->type->bytepp;
	for (i = 0; i < mdev_state->type->height; i++)
		memset(mdev_state->memblk + i * stride,
		       i * 255 / mdev_state->type->height,
		       stride);
	return 0;
}