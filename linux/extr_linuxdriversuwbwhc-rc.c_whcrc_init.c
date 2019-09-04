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
struct whcrc {int /*<<< orphan*/  event_work; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  whcrc_event_work ; 

__attribute__((used)) static void whcrc_init(struct whcrc *whcrc)
{
	spin_lock_init(&whcrc->irq_lock);
	init_waitqueue_head(&whcrc->cmd_wq);
	INIT_WORK(&whcrc->event_work, whcrc_event_work);
}