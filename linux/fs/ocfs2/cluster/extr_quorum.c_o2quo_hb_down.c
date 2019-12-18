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
typedef  int /*<<< orphan*/  u8 ;
struct o2quo_state {scalar_t__ qs_heartbeating; int /*<<< orphan*/  qs_lock; int /*<<< orphan*/  qs_hb_bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  o2quo_clear_hold (struct o2quo_state*,int /*<<< orphan*/ ) ; 
 struct o2quo_state o2quo_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void o2quo_hb_down(u8 node)
{
	struct o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	qs->qs_heartbeating--;
	mlog_bug_on_msg(qs->qs_heartbeating < 0,
			"node %u, %d heartbeating\n",
			node, qs->qs_heartbeating);
	mlog_bug_on_msg(!test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	clear_bit(node, qs->qs_hb_bm);

	mlog(0, "node %u, %d total\n", node, qs->qs_heartbeating);

	o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
}