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
struct sock_diag_handler {int family; } ;

/* Variables and functions */
 int AF_MAX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sock_diag_handler const** sock_diag_handlers ; 
 int /*<<< orphan*/  sock_diag_table_mutex ; 

void sock_diag_unregister(const struct sock_diag_handler *hnld)
{
	int family = hnld->family;

	if (family >= AF_MAX)
		return;

	mutex_lock(&sock_diag_table_mutex);
	BUG_ON(sock_diag_handlers[family] != hnld);
	sock_diag_handlers[family] = NULL;
	mutex_unlock(&sock_diag_table_mutex);
}