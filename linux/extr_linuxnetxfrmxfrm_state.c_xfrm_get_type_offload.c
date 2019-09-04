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
typedef  size_t u8 ;
struct xfrm_type_offload {int /*<<< orphan*/  owner; } ;
struct xfrm_state_afinfo {struct xfrm_type_offload** type_offload_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,unsigned short,size_t) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 

__attribute__((used)) static const struct xfrm_type_offload *
xfrm_get_type_offload(u8 proto, unsigned short family, bool try_load)
{
	struct xfrm_state_afinfo *afinfo;
	const struct xfrm_type_offload **typemap;
	const struct xfrm_type_offload *type;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return NULL;
	typemap = afinfo->type_offload_map;

	type = typemap[proto];
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