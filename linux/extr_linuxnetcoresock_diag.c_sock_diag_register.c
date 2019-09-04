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
struct sock_diag_handler {size_t family; } ;

/* Variables and functions */
 size_t AF_MAX ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sock_diag_handler const** sock_diag_handlers ; 
 int /*<<< orphan*/  sock_diag_table_mutex ; 

int sock_diag_register(const struct sock_diag_handler *hndl)
{
	int err = 0;

	if (hndl->family >= AF_MAX)
		return -EINVAL;

	mutex_lock(&sock_diag_table_mutex);
	if (sock_diag_handlers[hndl->family])
		err = -EBUSY;
	else
		sock_diag_handlers[hndl->family] = hndl;
	mutex_unlock(&sock_diag_table_mutex);

	return err;
}