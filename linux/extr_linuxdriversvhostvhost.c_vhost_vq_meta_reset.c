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
 int /*<<< orphan*/  __vhost_vq_meta_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vhost_vq_meta_reset(struct vhost_dev *d)
{
	int i;

	for (i = 0; i < d->nvqs; ++i)
		__vhost_vq_meta_reset(d->vqs[i]);
}