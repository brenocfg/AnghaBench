#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_NO_TRUNCATE ; 
 int affs_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
affs_nofilenametruncate(const struct dentry *dentry)
{
	return affs_test_opt(AFFS_SB(dentry->d_sb)->s_flags, SF_NO_TRUNCATE);
}