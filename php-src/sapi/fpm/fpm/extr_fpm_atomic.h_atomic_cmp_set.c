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
typedef  unsigned char atomic_uint_t ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */

__attribute__((used)) static inline atomic_uint_t atomic_cmp_set(atomic_t *lock, atomic_uint_t old, atomic_uint_t set) /* {{{ */
{
	unsigned char res;

	__asm__ volatile ( "lock;" "cmpxchgq %3, %1;" "sete %0;" :
		"=a" (res) : "m" (*lock), "a" (old), "r" (set) : "memory");

	return res;
}