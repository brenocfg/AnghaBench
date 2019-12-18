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
struct nlattr {int dummy; } ;
struct libbpf_nla_policy {size_t type; int minlen; int maxlen; } ;

/* Variables and functions */
 size_t LIBBPF_NLA_STRING ; 
 size_t LIBBPF_NLA_TYPE_MAX ; 
 size_t LIBBPF_NLA_UNSPEC ; 
 char* libbpf_nla_data (struct nlattr*) ; 
 int libbpf_nla_len (struct nlattr*) ; 
 unsigned int* nla_attr_minlen ; 
 int nla_type (struct nlattr*) ; 

__attribute__((used)) static int validate_nla(struct nlattr *nla, int maxtype,
			struct libbpf_nla_policy *policy)
{
	struct libbpf_nla_policy *pt;
	unsigned int minlen = 0;
	int type = nla_type(nla);

	if (type < 0 || type > maxtype)
		return 0;

	pt = &policy[type];

	if (pt->type > LIBBPF_NLA_TYPE_MAX)
		return 0;

	if (pt->minlen)
		minlen = pt->minlen;
	else if (pt->type != LIBBPF_NLA_UNSPEC)
		minlen = nla_attr_minlen[pt->type];

	if (libbpf_nla_len(nla) < minlen)
		return -1;

	if (pt->maxlen && libbpf_nla_len(nla) > pt->maxlen)
		return -1;

	if (pt->type == LIBBPF_NLA_STRING) {
		char *data = libbpf_nla_data(nla);

		if (data[libbpf_nla_len(nla) - 1] != '\0')
			return -1;
	}

	return 0;
}