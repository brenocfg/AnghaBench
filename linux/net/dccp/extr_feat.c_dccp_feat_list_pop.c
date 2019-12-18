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
struct dccp_feat_entry {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_feat_entry_destructor (struct dccp_feat_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dccp_feat_list_pop(struct dccp_feat_entry *entry)
{
	list_del(&entry->node);
	dccp_feat_entry_destructor(entry);
}