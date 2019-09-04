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
struct nls_table {struct nls_table* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nls_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct nls_table* tables ; 

int unregister_nls(struct nls_table * nls)
{
	struct nls_table ** tmp = &tables;

	spin_lock(&nls_lock);
	while (*tmp) {
		if (nls == *tmp) {
			*tmp = nls->next;
			spin_unlock(&nls_lock);
			return 0;
		}
		tmp = &(*tmp)->next;
	}
	spin_unlock(&nls_lock);
	return -EINVAL;
}