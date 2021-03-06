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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct swap_info_struct* _swap_info_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct swap_info_struct *swap_info_get_cont(swp_entry_t entry,
					struct swap_info_struct *q)
{
	struct swap_info_struct *p;

	p = _swap_info_get(entry);

	if (p != q) {
		if (q != NULL)
			spin_unlock(&q->lock);
		if (p != NULL)
			spin_lock(&p->lock);
	}
	return p;
}