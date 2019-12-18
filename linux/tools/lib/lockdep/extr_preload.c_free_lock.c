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
struct lock_lookup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lock_lookup*) ; 
 int /*<<< orphan*/  is_static_lock (struct lock_lookup*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void free_lock(struct lock_lookup *lock)
{
	if (likely(!is_static_lock(lock)))
		free(lock);
}