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
struct netns_ipvs {int /*<<< orphan*/  est_lock; int /*<<< orphan*/  est_list; } ;
struct ip_vs_estimator {int /*<<< orphan*/  list; } ;
struct ip_vs_stats {struct ip_vs_estimator est; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_vs_start_estimator(struct netns_ipvs *ipvs, struct ip_vs_stats *stats)
{
	struct ip_vs_estimator *est = &stats->est;

	INIT_LIST_HEAD(&est->list);

	spin_lock_bh(&ipvs->est_lock);
	list_add(&est->list, &ipvs->est_list);
	spin_unlock_bh(&ipvs->est_lock);
}