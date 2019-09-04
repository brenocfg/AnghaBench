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
struct tcphdr {scalar_t__ ack; scalar_t__ fin; scalar_t__ syn; scalar_t__ rst; } ;

/* Variables and functions */

__attribute__((used)) static inline int tcp_state_idx(struct tcphdr *th)
{
	if (th->rst)
		return 3;
	if (th->syn)
		return 0;
	if (th->fin)
		return 1;
	if (th->ack)
		return 2;
	return -1;
}