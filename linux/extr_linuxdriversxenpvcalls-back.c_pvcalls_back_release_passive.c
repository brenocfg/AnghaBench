#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int dummy; } ;
struct sockpass_mapping {int /*<<< orphan*/  wq; TYPE_2__* sock; int /*<<< orphan*/  saved_data_ready; } ;
struct pvcalls_fedata {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sockpass_mapping*) ; 
 int /*<<< orphan*/  sock_release (TYPE_2__*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvcalls_back_release_passive(struct xenbus_device *dev,
					struct pvcalls_fedata *fedata,
					struct sockpass_mapping *mappass)
{
	if (mappass->sock->sk != NULL) {
		write_lock_bh(&mappass->sock->sk->sk_callback_lock);
		mappass->sock->sk->sk_user_data = NULL;
		mappass->sock->sk->sk_data_ready = mappass->saved_data_ready;
		write_unlock_bh(&mappass->sock->sk->sk_callback_lock);
	}
	sock_release(mappass->sock);
	flush_workqueue(mappass->wq);
	destroy_workqueue(mappass->wq);
	kfree(mappass);

	return 0;
}