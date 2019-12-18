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
struct ip_vs_service {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_vs_del_service (struct ip_vs_service*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_svc_unhash (struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_unregister_conntrack (struct ip_vs_service*) ; 

__attribute__((used)) static void ip_vs_unlink_service(struct ip_vs_service *svc, bool cleanup)
{
	ip_vs_unregister_conntrack(svc);
	/* Hold svc to avoid double release from dest_trash */
	atomic_inc(&svc->refcnt);
	/*
	 * Unhash it from the service table
	 */
	ip_vs_svc_unhash(svc);

	__ip_vs_del_service(svc, cleanup);
}