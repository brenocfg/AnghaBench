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
struct o2quo_state {int /*<<< orphan*/  qs_work; int /*<<< orphan*/  qs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2quo_make_decision ; 
 struct o2quo_state o2quo_state ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void o2quo_init(void)
{
	struct o2quo_state *qs = &o2quo_state;

	spin_lock_init(&qs->qs_lock);
	INIT_WORK(&qs->qs_work, o2quo_make_decision);
}