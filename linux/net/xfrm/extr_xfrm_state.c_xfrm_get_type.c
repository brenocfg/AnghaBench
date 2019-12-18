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
struct xfrm_type {int /*<<< orphan*/  owner; } ;
struct xfrm_state_afinfo {struct xfrm_type* type_ipip6; struct xfrm_type* type_routing; struct xfrm_type* type_dstopts; struct xfrm_type* type_ipip; struct xfrm_type* type_esp; struct xfrm_type* type_ah; struct xfrm_type* type_comp; } ;

/* Variables and functions */
#define  IPPROTO_AH 134 
#define  IPPROTO_COMP 133 
#define  IPPROTO_DSTOPTS 132 
#define  IPPROTO_ESP 131 
#define  IPPROTO_IPIP 130 
#define  IPPROTO_IPV6 129 
#define  IPPROTO_ROUTING 128 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,unsigned short,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned short) ; 

__attribute__((used)) static const struct xfrm_type *xfrm_get_type(u8 proto, unsigned short family)
{
	const struct xfrm_type *type = NULL;
	struct xfrm_state_afinfo *afinfo;
	int modload_attempted = 0;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return NULL;

	switch (proto) {
	case IPPROTO_COMP:
		type = afinfo->type_comp;
		break;
	case IPPROTO_AH:
		type = afinfo->type_ah;
		break;
	case IPPROTO_ESP:
		type = afinfo->type_esp;
		break;
	case IPPROTO_IPIP:
		type = afinfo->type_ipip;
		break;
	case IPPROTO_DSTOPTS:
		type = afinfo->type_dstopts;
		break;
	case IPPROTO_ROUTING:
		type = afinfo->type_routing;
		break;
	case IPPROTO_IPV6:
		type = afinfo->type_ipip6;
		break;
	default:
		break;
	}

	if (unlikely(type && !try_module_get(type->owner)))
		type = NULL;

	rcu_read_unlock();

	if (!type && !modload_attempted) {
		request_module("xfrm-type-%d-%d", family, proto);
		modload_attempted = 1;
		goto retry;
	}

	return type;
}