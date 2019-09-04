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
struct ip_vs_sh_state {int dummy; } ;
struct ip_vs_service {struct ip_vs_sh_state* sched_data; } ;
struct ip_vs_dest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_sh_reassign (struct ip_vs_sh_state*,struct ip_vs_service*) ; 

__attribute__((used)) static int ip_vs_sh_dest_changed(struct ip_vs_service *svc,
				 struct ip_vs_dest *dest)
{
	struct ip_vs_sh_state *s = svc->sched_data;

	/* assign the hash buckets with the updated service */
	ip_vs_sh_reassign(s, svc);

	return 0;
}