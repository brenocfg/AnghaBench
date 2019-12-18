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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_metrics_block {int /*<<< orphan*/ * tcpm_vals; } ;
typedef  enum tcp_metric_index { ____Placeholder_tcp_metric_index } tcp_metric_index ;

/* Variables and functions */

__attribute__((used)) static void tcp_metric_set(struct tcp_metrics_block *tm,
			   enum tcp_metric_index idx,
			   u32 val)
{
	tm->tcpm_vals[idx] = val;
}