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
typedef  int /*<<< orphan*/  u8 ;
struct dccp_feat_entry {scalar_t__ is_local; scalar_t__ needs_confirm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPO_CHANGE_L ; 
 int /*<<< orphan*/  DCCPO_CHANGE_R ; 
 int /*<<< orphan*/  DCCPO_CONFIRM_L ; 
 int /*<<< orphan*/  DCCPO_CONFIRM_R ; 

__attribute__((used)) static inline u8 dccp_feat_genopt(struct dccp_feat_entry *entry)
{
	if (entry->needs_confirm)
		return entry->is_local ? DCCPO_CONFIRM_L : DCCPO_CONFIRM_R;
	return entry->is_local ? DCCPO_CHANGE_L : DCCPO_CHANGE_R;
}