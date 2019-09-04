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
struct sit_entry_set {int /*<<< orphan*/  set_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sit_entry_set*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sit_entry_set_slab ; 

__attribute__((used)) static void release_sit_entry_set(struct sit_entry_set *ses)
{
	list_del(&ses->set_list);
	kmem_cache_free(sit_entry_set_slab, ses);
}