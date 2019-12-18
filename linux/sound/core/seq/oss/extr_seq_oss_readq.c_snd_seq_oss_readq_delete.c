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
struct seq_oss_readq {struct seq_oss_readq* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct seq_oss_readq*) ; 

void
snd_seq_oss_readq_delete(struct seq_oss_readq *q)
{
	if (q) {
		kfree(q->q);
		kfree(q);
	}
}