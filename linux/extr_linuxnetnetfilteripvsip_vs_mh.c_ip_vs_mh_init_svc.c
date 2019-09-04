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
struct ip_vs_service {struct ip_vs_mh_state* sched_data; } ;
struct ip_vs_mh_state {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  gcd; int /*<<< orphan*/  rshift; int /*<<< orphan*/  hash2; int /*<<< orphan*/  hash1; int /*<<< orphan*/  lookup; } ;
struct ip_vs_mh_lookup {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int) ; 
 int IP_VS_MH_TAB_SIZE ; 
 int /*<<< orphan*/  generate_hash_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_mh_gcd_weight (struct ip_vs_service*) ; 
 int ip_vs_mh_reassign (struct ip_vs_mh_state*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_mh_reset (struct ip_vs_mh_state*) ; 
 int /*<<< orphan*/  ip_vs_mh_shift_weight (struct ip_vs_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_mh_state_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_mh_state*) ; 
 struct ip_vs_mh_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_mh_init_svc(struct ip_vs_service *svc)
{
	int ret;
	struct ip_vs_mh_state *s;

	/* Allocate the MH table for this service */
	s = kzalloc(sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->lookup = kcalloc(IP_VS_MH_TAB_SIZE, sizeof(struct ip_vs_mh_lookup),
			    GFP_KERNEL);
	if (!s->lookup) {
		kfree(s);
		return -ENOMEM;
	}

	generate_hash_secret(&s->hash1, &s->hash2);
	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->rshift = ip_vs_mh_shift_weight(svc, s->gcd);

	IP_VS_DBG(6,
		  "MH lookup table (memory=%zdbytes) allocated for current service\n",
		  sizeof(struct ip_vs_mh_lookup) * IP_VS_MH_TAB_SIZE);

	/* Assign the lookup table with current dests */
	ret = ip_vs_mh_reassign(s, svc);
	if (ret < 0) {
		ip_vs_mh_reset(s);
		ip_vs_mh_state_free(&s->rcu_head);
		return ret;
	}

	/* No more failures, attach state */
	svc->sched_data = s;
	return 0;
}