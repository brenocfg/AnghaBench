#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  register_work; } ;
struct sock_mapping {void* bytes; TYPE_3__* sock; int /*<<< orphan*/  irq; scalar_t__ ring; TYPE_2__ ioworker; int /*<<< orphan*/  release; int /*<<< orphan*/  saved_data_ready; } ;
struct pvcalls_fedata {int dummy; } ;
struct TYPE_6__ {TYPE_1__* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sock_mapping*) ; 
 int /*<<< orphan*/  sock_release (TYPE_3__*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int /*<<< orphan*/ ,struct sock_mapping*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (struct xenbus_device*,void*) ; 

__attribute__((used)) static int pvcalls_back_release_active(struct xenbus_device *dev,
				       struct pvcalls_fedata *fedata,
				       struct sock_mapping *map)
{
	disable_irq(map->irq);
	if (map->sock->sk != NULL) {
		write_lock_bh(&map->sock->sk->sk_callback_lock);
		map->sock->sk->sk_user_data = NULL;
		map->sock->sk->sk_data_ready = map->saved_data_ready;
		write_unlock_bh(&map->sock->sk->sk_callback_lock);
	}

	atomic_set(&map->release, 1);
	flush_work(&map->ioworker.register_work);

	xenbus_unmap_ring_vfree(dev, map->bytes);
	xenbus_unmap_ring_vfree(dev, (void *)map->ring);
	unbind_from_irqhandler(map->irq, map);

	sock_release(map->sock);
	kfree(map);

	return 0;
}