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
struct tcp_metrics_block {int /*<<< orphan*/  tcpm_net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net* read_pnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct net *tm_net(struct tcp_metrics_block *tm)
{
	return read_pnet(&tm->tcpm_net);
}