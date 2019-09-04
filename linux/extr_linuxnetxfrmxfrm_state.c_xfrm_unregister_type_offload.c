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
struct xfrm_type_offload {size_t proto; } ;
struct xfrm_state_afinfo {struct xfrm_type_offload** type_offload_map; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOENT ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 
 int /*<<< orphan*/  xfrm_type_offload_lock ; 

int xfrm_unregister_type_offload(const struct xfrm_type_offload *type,
				 unsigned short family)
{
	struct xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);
	const struct xfrm_type_offload **typemap;
	int err = 0;

	if (unlikely(afinfo == NULL))
		return -EAFNOSUPPORT;
	typemap = afinfo->type_offload_map;
	spin_lock_bh(&xfrm_type_offload_lock);

	if (unlikely(typemap[type->proto] != type))
		err = -ENOENT;
	else
		typemap[type->proto] = NULL;
	spin_unlock_bh(&xfrm_type_offload_lock);
	rcu_read_unlock();
	return err;
}