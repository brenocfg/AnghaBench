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
struct ds_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds_w1_fini(struct ds_device *dev)
{
	w1_remove_master_device(&dev->master);
}