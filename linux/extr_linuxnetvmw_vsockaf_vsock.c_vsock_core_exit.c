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

/* Variables and functions */
 int /*<<< orphan*/  AF_VSOCK ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transport ; 
 int /*<<< orphan*/  vsock_device ; 
 int /*<<< orphan*/  vsock_proto ; 
 int /*<<< orphan*/  vsock_register_mutex ; 

void vsock_core_exit(void)
{
	mutex_lock(&vsock_register_mutex);

	misc_deregister(&vsock_device);
	sock_unregister(AF_VSOCK);
	proto_unregister(&vsock_proto);

	/* We do not want the assignment below re-ordered. */
	mb();
	transport = NULL;

	mutex_unlock(&vsock_register_mutex);
}