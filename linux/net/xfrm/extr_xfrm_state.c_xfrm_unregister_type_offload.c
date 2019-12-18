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
struct xfrm_type_offload {int proto; } ;
struct xfrm_state_afinfo {struct xfrm_type_offload const* type_offload_esp; } ;

/* Variables and functions */
#define  IPPROTO_ESP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 

void xfrm_unregister_type_offload(const struct xfrm_type_offload *type,
				  unsigned short family)
{
	struct xfrm_state_afinfo *afinfo = xfrm_state_get_afinfo(family);

	if (unlikely(afinfo == NULL))
		return;

	switch (type->proto) {
	case IPPROTO_ESP:
		WARN_ON(afinfo->type_offload_esp != type);
		afinfo->type_offload_esp = NULL;
		break;
	default:
		WARN_ON(1);
		break;
	}
	rcu_read_unlock();
}