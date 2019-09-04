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

/* Variables and functions */
 size_t TOMOYO_MEMORY_POLICY ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ ksize (void*) ; 
 int /*<<< orphan*/ * tomoyo_memory_used ; 

__attribute__((used)) static inline void tomoyo_memory_free(void *ptr)
{
	tomoyo_memory_used[TOMOYO_MEMORY_POLICY] -= ksize(ptr);
	kfree(ptr);
}