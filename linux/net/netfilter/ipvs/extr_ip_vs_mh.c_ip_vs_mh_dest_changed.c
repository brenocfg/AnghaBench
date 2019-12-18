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
struct ip_vs_mh_state {int /*<<< orphan*/  gcd; int /*<<< orphan*/  rshift; } ;
struct ip_vs_dest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_mh_gcd_weight (struct ip_vs_service*) ; 
 int ip_vs_mh_reassign (struct ip_vs_mh_state*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_mh_shift_weight (struct ip_vs_service*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_mh_dest_changed(struct ip_vs_service *svc,
				 struct ip_vs_dest *dest)
{
	struct ip_vs_mh_state *s = svc->sched_data;

	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->rshift = ip_vs_mh_shift_weight(svc, s->gcd);

	/* Assign the lookup table with the updated service */
	return ip_vs_mh_reassign(s, svc);
}