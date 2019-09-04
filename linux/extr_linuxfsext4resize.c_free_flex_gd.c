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
struct ext4_new_flex_group_data {struct ext4_new_flex_group_data* groups; struct ext4_new_flex_group_data* bg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ext4_new_flex_group_data*) ; 

__attribute__((used)) static void free_flex_gd(struct ext4_new_flex_group_data *flex_gd)
{
	kfree(flex_gd->bg_flags);
	kfree(flex_gd->groups);
	kfree(flex_gd);
}