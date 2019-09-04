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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct vhost_net {TYPE_1__ dev; TYPE_3__* vqs; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  acked_backend_features; } ;
struct TYPE_6__ {TYPE_2__ vq; } ;

/* Variables and functions */
 int VHOST_NET_VQ_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhost_net_set_backend_features(struct vhost_net *n, u64 features)
{
	int i;

	mutex_lock(&n->dev.mutex);
	for (i = 0; i < VHOST_NET_VQ_MAX; ++i) {
		mutex_lock(&n->vqs[i].vq.mutex);
		n->vqs[i].vq.acked_backend_features = features;
		mutex_unlock(&n->vqs[i].vq.mutex);
	}
	mutex_unlock(&n->dev.mutex);

	return 0;
}