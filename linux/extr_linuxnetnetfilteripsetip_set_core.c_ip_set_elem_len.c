#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct ip_set {size_t* offset; int /*<<< orphan*/  extensions; int /*<<< orphan*/  flags; } ;
typedef  enum ip_set_ext_id { ____Placeholder_ip_set_ext_id } ip_set_ext_id ;
struct TYPE_2__ {size_t align; scalar_t__ len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t ALIGN (size_t,size_t) ; 
 size_t IPSET_ATTR_CADT_FLAGS ; 
 int /*<<< orphan*/  IPSET_CREATE_FLAG_FORCEADD ; 
 int IPSET_EXT_ID_MAX ; 
 int IPSET_FLAG_WITH_FORCEADD ; 
 int /*<<< orphan*/  add_extension (int,int,struct nlattr**) ; 
 TYPE_1__* ip_set_extensions ; 
 int ip_set_get_h32 (struct nlattr*) ; 

size_t
ip_set_elem_len(struct ip_set *set, struct nlattr *tb[], size_t len,
		size_t align)
{
	enum ip_set_ext_id id;
	u32 cadt_flags = 0;

	if (tb[IPSET_ATTR_CADT_FLAGS])
		cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);
	if (cadt_flags & IPSET_FLAG_WITH_FORCEADD)
		set->flags |= IPSET_CREATE_FLAG_FORCEADD;
	if (!align)
		align = 1;
	for (id = 0; id < IPSET_EXT_ID_MAX; id++) {
		if (!add_extension(id, cadt_flags, tb))
			continue;
		len = ALIGN(len, ip_set_extensions[id].align);
		set->offset[id] = len;
		set->extensions |= ip_set_extensions[id].type;
		len += ip_set_extensions[id].len;
	}
	return ALIGN(len, align);
}