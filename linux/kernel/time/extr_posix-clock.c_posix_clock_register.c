#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct posix_clock {TYPE_2__ cdev; TYPE_1__ ops; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  kref; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int cdev_add (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_clock_file_operations ; 

int posix_clock_register(struct posix_clock *clk, dev_t devid)
{
	int err;

	kref_init(&clk->kref);
	init_rwsem(&clk->rwsem);

	cdev_init(&clk->cdev, &posix_clock_file_operations);
	clk->cdev.owner = clk->ops.owner;
	err = cdev_add(&clk->cdev, devid, 1);

	return err;
}