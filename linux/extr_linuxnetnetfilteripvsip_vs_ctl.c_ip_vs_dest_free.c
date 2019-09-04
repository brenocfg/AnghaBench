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
struct ip_vs_service {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpustats; } ;
struct ip_vs_dest {TYPE_1__ stats; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_vs_dst_cache_reset (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  __ip_vs_svc_put (struct ip_vs_service*,int) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_dest_put_and_free (struct ip_vs_dest*) ; 
 struct ip_vs_service* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ip_vs_dest_free(struct ip_vs_dest *dest)
{
	struct ip_vs_service *svc = rcu_dereference_protected(dest->svc, 1);

	__ip_vs_dst_cache_reset(dest);
	__ip_vs_svc_put(svc, false);
	free_percpu(dest->stats.cpustats);
	ip_vs_dest_put_and_free(dest);
}