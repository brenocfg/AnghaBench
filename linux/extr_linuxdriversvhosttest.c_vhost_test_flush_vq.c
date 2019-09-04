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
struct vhost_test {TYPE_1__* vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_poll_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_test_flush_vq(struct vhost_test *n, int index)
{
	vhost_poll_flush(&n->vqs[index].poll);
}