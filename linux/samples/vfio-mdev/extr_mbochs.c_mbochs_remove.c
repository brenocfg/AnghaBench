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
struct mdev_state {struct mdev_state* vconfig; struct mdev_state* pages; TYPE_1__* type; } ;
struct mdev_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ mbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mdev_state*) ; 
 int /*<<< orphan*/  mbochs_used_mbytes ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_set_drvdata (struct mdev_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mbochs_remove(struct mdev_device *mdev)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);

	mbochs_used_mbytes -= mdev_state->type->mbytes;
	mdev_set_drvdata(mdev, NULL);
	kfree(mdev_state->pages);
	kfree(mdev_state->vconfig);
	kfree(mdev_state);
	return 0;
}