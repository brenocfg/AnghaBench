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
struct ip_vs_sh_bucket {int dummy; } ;
struct ip_vs_service {struct ip_vs_sh_state* sched_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int) ; 
 int IP_VS_SH_TAB_SIZE ; 
 int /*<<< orphan*/  ip_vs_sh_reassign (struct ip_vs_sh_state*,struct ip_vs_service*) ; 
 struct ip_vs_sh_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_sh_init_svc(struct ip_vs_service *svc)
{
	struct ip_vs_sh_state *s;

	/* allocate the SH table for this service */
	s = kzalloc(sizeof(struct ip_vs_sh_state), GFP_KERNEL);
	if (s == NULL)
		return -ENOMEM;

	svc->sched_data = s;
	IP_VS_DBG(6, "SH hash table (memory=%zdbytes) allocated for "
		  "current service\n",
		  sizeof(struct ip_vs_sh_bucket)*IP_VS_SH_TAB_SIZE);

	/* assign the hash buckets with current dests */
	ip_vs_sh_reassign(s, svc);

	return 0;
}