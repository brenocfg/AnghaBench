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
struct path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_GETATTR ; 
 int /*<<< orphan*/  OP_GETATTR ; 
 int common_perm_cond (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_inode_getattr(const struct path *path)
{
	return common_perm_cond(OP_GETATTR, path, AA_MAY_GETATTR);
}