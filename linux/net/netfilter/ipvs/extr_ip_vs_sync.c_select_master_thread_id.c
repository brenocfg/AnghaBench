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
struct netns_ipvs {long threads_mask; } ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int ilog2 (int) ; 

__attribute__((used)) static inline int
select_master_thread_id(struct netns_ipvs *ipvs, struct ip_vs_conn *cp)
{
	return ((long) cp >> (1 + ilog2(sizeof(*cp)))) & ipvs->threads_mask;
}