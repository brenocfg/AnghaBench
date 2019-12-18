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
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;
struct TYPE_3__ {int offset; int /*<<< orphan*/  ptr; } ;
union futex_key {TYPE_2__ shared; TYPE_1__ both; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MMU ; 
#define  FUT_OFF_INODE 129 
#define  FUT_OFF_MMSHARED 128 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_get_mm (union futex_key*) ; 
 int /*<<< orphan*/  ihold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void get_futex_key_refs(union futex_key *key)
{
	if (!key->both.ptr)
		return;

	/*
	 * On MMU less systems futexes are always "private" as there is no per
	 * process address space. We need the smp wmb nevertheless - yes,
	 * arch/blackfin has MMU less SMP ...
	 */
	if (!IS_ENABLED(CONFIG_MMU)) {
		smp_mb(); /* explicit smp_mb(); (B) */
		return;
	}

	switch (key->both.offset & (FUT_OFF_INODE|FUT_OFF_MMSHARED)) {
	case FUT_OFF_INODE:
		ihold(key->shared.inode); /* implies smp_mb(); (B) */
		break;
	case FUT_OFF_MMSHARED:
		futex_get_mm(key); /* implies smp_mb(); (B) */
		break;
	default:
		/*
		 * Private futexes do not hold reference on an inode or
		 * mm, therefore the only purpose of calling get_futex_key_refs
		 * is because we need the barrier for the lockless waiter check.
		 */
		smp_mb(); /* explicit smp_mb(); (B) */
	}
}