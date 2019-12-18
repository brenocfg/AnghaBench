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
struct inet_diag_handler {size_t idiag_type; } ;
typedef  size_t __u16 ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 size_t const IPPROTO_MAX ; 
 struct inet_diag_handler const** inet_diag_table ; 
 int /*<<< orphan*/  inet_diag_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int inet_diag_register(const struct inet_diag_handler *h)
{
	const __u16 type = h->idiag_type;
	int err = -EINVAL;

	if (type >= IPPROTO_MAX)
		goto out;

	mutex_lock(&inet_diag_table_mutex);
	err = -EEXIST;
	if (!inet_diag_table[type]) {
		inet_diag_table[type] = h;
		err = 0;
	}
	mutex_unlock(&inet_diag_table_mutex);
out:
	return err;
}