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
struct work_struct {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  work_pending (struct work_struct*) ; 
 unsigned long work_static (struct work_struct*) ; 

__attribute__((used)) static inline void set_work_data(struct work_struct *work, unsigned long data,
				 unsigned long flags)
{
	WARN_ON_ONCE(!work_pending(work));
	atomic_long_set(&work->data, data | flags | work_static(work));
}