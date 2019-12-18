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
struct fq_codel_sched_data {int /*<<< orphan*/  flows_cnt; } ;

/* Variables and functions */
 unsigned int reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_hash (struct sk_buff*) ; 

__attribute__((used)) static unsigned int fq_codel_hash(const struct fq_codel_sched_data *q,
				  struct sk_buff *skb)
{
	return reciprocal_scale(skb_get_hash(skb), q->flows_cnt);
}