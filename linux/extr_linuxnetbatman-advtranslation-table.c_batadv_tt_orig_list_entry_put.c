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
struct batadv_tt_orig_list_entry {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_tt_orig_list_entry_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
batadv_tt_orig_list_entry_put(struct batadv_tt_orig_list_entry *orig_entry)
{
	kref_put(&orig_entry->refcount, batadv_tt_orig_list_entry_release);
}