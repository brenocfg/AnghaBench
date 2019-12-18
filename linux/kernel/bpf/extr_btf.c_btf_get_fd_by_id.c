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
typedef  int /*<<< orphan*/  u32 ;
struct btf {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct btf* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct btf*) ; 
 int PTR_ERR (struct btf*) ; 
 int __btf_new_fd (struct btf*) ; 
 int /*<<< orphan*/  btf_idr ; 
 int /*<<< orphan*/  btf_put (struct btf*) ; 
 struct btf* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

int btf_get_fd_by_id(u32 id)
{
	struct btf *btf;
	int fd;

	rcu_read_lock();
	btf = idr_find(&btf_idr, id);
	if (!btf || !refcount_inc_not_zero(&btf->refcnt))
		btf = ERR_PTR(-ENOENT);
	rcu_read_unlock();

	if (IS_ERR(btf))
		return PTR_ERR(btf);

	fd = __btf_new_fd(btf);
	if (fd < 0)
		btf_put(btf);

	return fd;
}