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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __efivar_entry_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivarfs_destroy ; 
 int /*<<< orphan*/  efivarfs_list ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 

__attribute__((used)) static void efivarfs_kill_sb(struct super_block *sb)
{
	kill_litter_super(sb);

	/* Remove all entries and destroy */
	__efivar_entry_iter(efivarfs_destroy, &efivarfs_list, NULL, NULL);
}