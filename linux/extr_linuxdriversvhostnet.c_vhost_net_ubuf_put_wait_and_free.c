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
struct vhost_net_ubuf_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vhost_net_ubuf_ref*) ; 
 int /*<<< orphan*/  vhost_net_ubuf_put_and_wait (struct vhost_net_ubuf_ref*) ; 

__attribute__((used)) static void vhost_net_ubuf_put_wait_and_free(struct vhost_net_ubuf_ref *ubufs)
{
	vhost_net_ubuf_put_and_wait(ubufs);
	kfree(ubufs);
}