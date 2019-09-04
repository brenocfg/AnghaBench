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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_inode_lower (struct inode*) ; 

__attribute__((used)) static bool ovl_should_check_upperdata(struct inode *inode)
{
	if (!S_ISREG(inode->i_mode))
		return false;

	if (!ovl_inode_lower(inode))
		return false;

	return true;
}