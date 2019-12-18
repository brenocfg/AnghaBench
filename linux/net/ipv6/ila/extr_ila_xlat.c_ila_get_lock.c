#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t locks_mask; int /*<<< orphan*/ * locks; } ;
struct ila_net {TYPE_1__ xlat; } ;
struct ila_locator {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 size_t ila_locator_hash (struct ila_locator) ; 

__attribute__((used)) static inline spinlock_t *ila_get_lock(struct ila_net *ilan,
				       struct ila_locator loc)
{
	return &ilan->xlat.locks[ila_locator_hash(loc) & ilan->xlat.locks_mask];
}