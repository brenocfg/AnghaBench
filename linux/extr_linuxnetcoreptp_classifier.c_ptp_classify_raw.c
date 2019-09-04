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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int BPF_PROG_RUN (int /*<<< orphan*/ ,struct sk_buff const*) ; 
 int /*<<< orphan*/  ptp_insns ; 

unsigned int ptp_classify_raw(const struct sk_buff *skb)
{
	return BPF_PROG_RUN(ptp_insns, skb);
}