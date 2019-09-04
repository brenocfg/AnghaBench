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
struct ip_set_net {scalar_t__ ip_set_max; } ;
struct ip_set {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int EEXIST ; 
 int IPSET_ERR_MAX_SETS ; 
 scalar_t__ IPSET_INVALID_ID ; 
 scalar_t__ STRNCMP (char const*,int /*<<< orphan*/ ) ; 
 struct ip_set* ip_set (struct ip_set_net*,scalar_t__) ; 

__attribute__((used)) static int
find_free_id(struct ip_set_net *inst, const char *name, ip_set_id_t *index,
	     struct ip_set **set)
{
	struct ip_set *s;
	ip_set_id_t i;

	*index = IPSET_INVALID_ID;
	for (i = 0;  i < inst->ip_set_max; i++) {
		s = ip_set(inst, i);
		if (!s) {
			if (*index == IPSET_INVALID_ID)
				*index = i;
		} else if (STRNCMP(name, s->name)) {
			/* Name clash */
			*set = s;
			return -EEXIST;
		}
	}
	if (*index == IPSET_INVALID_ID)
		/* No free slot remained */
		return -IPSET_ERR_MAX_SETS;
	return 0;
}