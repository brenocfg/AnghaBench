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
struct ipvs_master_sync_state {int dummy; } ;
struct ip_vs_sync_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPVS_SYNC_FLUSH_TIME ; 
 struct ip_vs_sync_buff* get_curr_sync_buff (struct netns_ipvs*,struct ipvs_master_sync_state*,int /*<<< orphan*/ ) ; 
 struct ip_vs_sync_buff* sb_dequeue (struct netns_ipvs*,struct ipvs_master_sync_state*) ; 

__attribute__((used)) static inline struct ip_vs_sync_buff *
next_sync_buff(struct netns_ipvs *ipvs, struct ipvs_master_sync_state *ms)
{
	struct ip_vs_sync_buff *sb;

	sb = sb_dequeue(ipvs, ms);
	if (sb)
		return sb;
	/* Do not delay entries in buffer for more than 2 seconds */
	return get_curr_sync_buff(ipvs, ms, IPVS_SYNC_FLUSH_TIME);
}