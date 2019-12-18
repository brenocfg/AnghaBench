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
struct ip_vs_seq {int previous_delta; int delta; int /*<<< orphan*/  init_seq; } ;
struct ip_vs_conn {unsigned int flags; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void vs_seq_update(struct ip_vs_conn *cp, struct ip_vs_seq *vseq,
				 unsigned int flag, __u32 seq, int diff)
{
	/* spinlock is to keep updating cp->flags atomic */
	spin_lock_bh(&cp->lock);
	if (!(cp->flags & flag) || after(seq, vseq->init_seq)) {
		vseq->previous_delta = vseq->delta;
		vseq->delta += diff;
		vseq->init_seq = seq;
		cp->flags |= flag;
	}
	spin_unlock_bh(&cp->lock);
}