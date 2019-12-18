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
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;
union futex_key {TYPE_1__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static inline void futex_get_mm(union futex_key *key)
{
	mmgrab(key->private.mm);
	/*
	 * Ensure futex_get_mm() implies a full barrier such that
	 * get_futex_key() implies a full barrier. This is relied upon
	 * as smp_mb(); (B), see the ordering comment above.
	 */
	smp_mb__after_atomic();
}