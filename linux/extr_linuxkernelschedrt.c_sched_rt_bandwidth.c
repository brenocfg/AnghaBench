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
struct rt_rq {int dummy; } ;
struct rt_bandwidth {int dummy; } ;

/* Variables and functions */
 struct rt_bandwidth def_rt_bandwidth ; 

__attribute__((used)) static inline struct rt_bandwidth *sched_rt_bandwidth(struct rt_rq *rt_rq)
{
	return &def_rt_bandwidth;
}