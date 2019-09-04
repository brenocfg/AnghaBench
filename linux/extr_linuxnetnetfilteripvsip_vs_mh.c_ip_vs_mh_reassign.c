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
struct ip_vs_service {int num_dests; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;
struct ip_vs_mh_state {int /*<<< orphan*/ * dest_setup; } ;
struct ip_vs_mh_dest_setup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_MH_TAB_SIZE ; 
 int /*<<< orphan*/  ip_vs_mh_permutate (struct ip_vs_mh_state*,struct ip_vs_service*) ; 
 int ip_vs_mh_populate (struct ip_vs_mh_state*,struct ip_vs_service*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_mh_reassign(struct ip_vs_mh_state *s,
			     struct ip_vs_service *svc)
{
	int ret;

	if (svc->num_dests > IP_VS_MH_TAB_SIZE)
		return -EINVAL;

	if (svc->num_dests >= 1) {
		s->dest_setup = kcalloc(svc->num_dests,
					sizeof(struct ip_vs_mh_dest_setup),
					GFP_KERNEL);
		if (!s->dest_setup)
			return -ENOMEM;
	}

	ip_vs_mh_permutate(s, svc);

	ret = ip_vs_mh_populate(s, svc);
	if (ret < 0)
		goto out;

	IP_VS_DBG_BUF(6, "MH: reassign lookup table of %s:%u\n",
		      IP_VS_DBG_ADDR(svc->af, &svc->addr),
		      ntohs(svc->port));

out:
	if (svc->num_dests >= 1) {
		kfree(s->dest_setup);
		s->dest_setup = NULL;
	}
	return ret;
}