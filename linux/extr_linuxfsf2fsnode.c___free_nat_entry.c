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
struct nat_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nat_entry*) ; 
 int /*<<< orphan*/  nat_entry_slab ; 

__attribute__((used)) static void __free_nat_entry(struct nat_entry *e)
{
	kmem_cache_free(nat_entry_slab, e);
}