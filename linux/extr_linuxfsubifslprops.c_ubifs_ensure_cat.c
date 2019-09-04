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
struct ubifs_lprops {int flags; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int LPROPS_CAT_MASK ; 
 int LPROPS_UNCAT ; 
 int /*<<< orphan*/  ubifs_add_to_cat (struct ubifs_info*,struct ubifs_lprops*,int) ; 
 int ubifs_categorize_lprops (struct ubifs_info*,struct ubifs_lprops*) ; 
 int /*<<< orphan*/  ubifs_remove_from_cat (struct ubifs_info*,struct ubifs_lprops*,int) ; 

void ubifs_ensure_cat(struct ubifs_info *c, struct ubifs_lprops *lprops)
{
	int cat = lprops->flags & LPROPS_CAT_MASK;

	if (cat != LPROPS_UNCAT)
		return;
	cat = ubifs_categorize_lprops(c, lprops);
	if (cat == LPROPS_UNCAT)
		return;
	ubifs_remove_from_cat(c, lprops, LPROPS_UNCAT);
	ubifs_add_to_cat(c, lprops, cat);
}