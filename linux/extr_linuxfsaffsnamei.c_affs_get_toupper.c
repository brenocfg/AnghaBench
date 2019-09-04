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
typedef  int /*<<< orphan*/  toupper_t ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SF_INTL ; 
 int /*<<< orphan*/  affs_intl_toupper ; 
 scalar_t__ affs_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_toupper ; 

__attribute__((used)) static inline toupper_t
affs_get_toupper(struct super_block *sb)
{
	return affs_test_opt(AFFS_SB(sb)->s_flags, SF_INTL) ?
	       affs_intl_toupper : affs_toupper;
}