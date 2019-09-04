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
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 scalar_t__ ovl_redirect_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_type_merge_or_lower (struct dentry*) ; 

__attribute__((used)) static bool ovl_can_move(struct dentry *dentry)
{
	return ovl_redirect_dir(dentry->d_sb) ||
		!d_is_dir(dentry) || !ovl_type_merge_or_lower(dentry);
}