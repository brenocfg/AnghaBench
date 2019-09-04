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
struct csio_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  evt_free_q; } ;
struct csio_evt_msg {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DEC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_evt_activeq ; 
 int /*<<< orphan*/  n_evt_freeq ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_free_evt(struct csio_hw *hw, struct csio_evt_msg *evt_entry)
{
	if (evt_entry) {
		spin_lock_irq(&hw->lock);
		list_del_init(&evt_entry->list);
		list_add_tail(&evt_entry->list, &hw->evt_free_q);
		CSIO_DEC_STATS(hw, n_evt_activeq);
		CSIO_INC_STATS(hw, n_evt_freeq);
		spin_unlock_irq(&hw->lock);
	}
}