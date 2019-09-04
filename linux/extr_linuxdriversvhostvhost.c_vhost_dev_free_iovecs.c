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
struct vhost_dev {int nvqs; int /*<<< orphan*/ * vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_vq_free_iovecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vhost_dev_free_iovecs(struct vhost_dev *dev)
{
	int i;

	for (i = 0; i < dev->nvqs; ++i)
		vhost_vq_free_iovecs(dev->vqs[i]);
}