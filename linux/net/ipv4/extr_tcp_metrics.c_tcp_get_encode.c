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
struct tcp_metrics_block {int dummy; } ;

/* Variables and functions */
 int TCP_METRICS_RECLAIM_DEPTH ; 
 struct tcp_metrics_block* TCP_METRICS_RECLAIM_PTR ; 

__attribute__((used)) static struct tcp_metrics_block *tcp_get_encode(struct tcp_metrics_block *tm, int depth)
{
	if (tm)
		return tm;
	if (depth > TCP_METRICS_RECLAIM_DEPTH)
		return TCP_METRICS_RECLAIM_PTR;
	return NULL;
}