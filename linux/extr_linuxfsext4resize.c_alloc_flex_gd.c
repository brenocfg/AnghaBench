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
struct ext4_new_group_data {int dummy; } ;
struct ext4_new_flex_group_data {unsigned long count; struct ext4_new_flex_group_data* groups; int /*<<< orphan*/ * bg_flags; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  kfree (struct ext4_new_flex_group_data*) ; 
 struct ext4_new_flex_group_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kmalloc_array (unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ext4_new_flex_group_data *alloc_flex_gd(unsigned long flexbg_size)
{
	struct ext4_new_flex_group_data *flex_gd;

	flex_gd = kmalloc(sizeof(*flex_gd), GFP_NOFS);
	if (flex_gd == NULL)
		goto out3;

	if (flexbg_size >= UINT_MAX / sizeof(struct ext4_new_group_data))
		goto out2;
	flex_gd->count = flexbg_size;

	flex_gd->groups = kmalloc_array(flexbg_size,
					sizeof(struct ext4_new_group_data),
					GFP_NOFS);
	if (flex_gd->groups == NULL)
		goto out2;

	flex_gd->bg_flags = kmalloc_array(flexbg_size, sizeof(__u16),
					  GFP_NOFS);
	if (flex_gd->bg_flags == NULL)
		goto out1;

	return flex_gd;

out1:
	kfree(flex_gd->groups);
out2:
	kfree(flex_gd);
out3:
	return NULL;
}