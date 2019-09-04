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
struct hist_entry {scalar_t__ unfolded; scalar_t__ leaf; } ;
typedef  enum hierarchy_move_dir { ____Placeholder_hierarchy_move_dir } hierarchy_move_dir ;

/* Variables and functions */
 int HMD_FORCE_CHILD ; 
 int HMD_FORCE_SIBLING ; 

__attribute__((used)) static bool can_goto_child(struct hist_entry *he, enum hierarchy_move_dir hmd)
{
	if (he->leaf || hmd == HMD_FORCE_SIBLING)
		return false;

	if (he->unfolded || hmd == HMD_FORCE_CHILD)
		return true;

	return false;
}