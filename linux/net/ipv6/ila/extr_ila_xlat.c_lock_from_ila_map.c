#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ila_net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  locator_match; } ;
struct TYPE_4__ {TYPE_1__ ip; } ;
struct ila_map {TYPE_2__ xp; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ila_get_lock (struct ila_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline spinlock_t *lock_from_ila_map(struct ila_net *ilan,
					    struct ila_map *ila)
{
	return ila_get_lock(ilan, ila->xp.ip.locator_match);
}