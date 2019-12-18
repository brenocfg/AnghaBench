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
struct lock_impl {int locked; } ;

/* Variables and functions */

__attribute__((used)) static inline void lock_impl_init(struct lock_impl *lock)
{
	lock->locked = false;
}