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
struct z_erofs_pagevec_ctor {int /*<<< orphan*/  curr; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void z_erofs_pagevec_ctor_exit(struct z_erofs_pagevec_ctor *ctor,
					     bool atomic)
{
	if (!ctor->curr)
		return;

	if (atomic)
		kunmap_atomic(ctor->pages);
	else
		kunmap(ctor->curr);
}