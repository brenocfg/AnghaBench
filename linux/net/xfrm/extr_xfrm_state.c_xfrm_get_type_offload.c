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
typedef  int u8 ;
struct xfrm_type_offload {int /*<<< orphan*/  owner; } ;
struct xfrm_state_afinfo {struct xfrm_type_offload* type_offload_esp; } ;

/* Variables and functions */
#define  IPPROTO_ESP 128 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,unsigned short,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 

__attribute__((used)) static const struct xfrm_type_offload *
xfrm_get_type_offload(u8 proto, unsigned short family, bool try_load)
{
	const struct xfrm_type_offload *type = NULL;
	struct xfrm_state_afinfo *afinfo;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return NULL;

	switch (proto) {
	case IPPROTO_ESP:
		type = afinfo->type_offload_esp;
		break;
	default:
		break;
	}

	if ((type && !try_module_get(type->owner)))
		type = NULL;

	rcu_read_unlock();

	if (!type && try_load) {
		request_module("xfrm-offload-%d-%d", family, proto);
		try_load = false;
		goto retry;
	}

	return type;
}