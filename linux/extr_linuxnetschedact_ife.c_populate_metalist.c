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
struct tcf_ife_info {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int add_metainfo (struct tcf_ife_info*,int,void*,int,int) ; 
 int load_metaops_and_vet (int,void*,int,int) ; 
 int max_metacnt ; 
 void* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int populate_metalist(struct tcf_ife_info *ife, struct nlattr **tb,
			     bool exists, bool rtnl_held)
{
	int len = 0;
	int rc = 0;
	int i = 0;
	void *val;

	for (i = 1; i < max_metacnt; i++) {
		if (tb[i]) {
			val = nla_data(tb[i]);
			len = nla_len(tb[i]);

			rc = load_metaops_and_vet(i, val, len, rtnl_held);
			if (rc != 0)
				return rc;

			rc = add_metainfo(ife, i, val, len, exists);
			if (rc)
				return rc;
		}
	}

	return rc;
}