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
struct vhost_vsock {int /*<<< orphan*/  queued_replies; struct vhost_virtqueue* vqs; } ;
struct vhost_virtqueue {int num; } ;

/* Variables and functions */
 size_t VSOCK_VQ_TX ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static bool vhost_vsock_more_replies(struct vhost_vsock *vsock)
{
	struct vhost_virtqueue *vq = &vsock->vqs[VSOCK_VQ_TX];
	int val;

	smp_rmb(); /* paired with atomic_inc() and atomic_dec_return() */
	val = atomic_read(&vsock->queued_replies);

	return val < vq->num;
}