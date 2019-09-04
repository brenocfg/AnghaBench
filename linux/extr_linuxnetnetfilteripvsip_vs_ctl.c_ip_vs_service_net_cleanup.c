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
struct netns_ipvs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int /*<<< orphan*/  __ip_vs_mutex ; 
 int /*<<< orphan*/  ip_vs_flush (struct netns_ipvs*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ip_vs_service_net_cleanup(struct netns_ipvs *ipvs)
{
	EnterFunction(2);
	/* Check for "full" addressed entries */
	mutex_lock(&__ip_vs_mutex);
	ip_vs_flush(ipvs, true);
	mutex_unlock(&__ip_vs_mutex);
	LeaveFunction(2);
}