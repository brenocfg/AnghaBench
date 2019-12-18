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
 int /*<<< orphan*/  EROFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool erofs_xattr_user_list(struct dentry *dentry)
{
	return test_opt(EROFS_SB(dentry->d_sb), XATTR_USER);
}