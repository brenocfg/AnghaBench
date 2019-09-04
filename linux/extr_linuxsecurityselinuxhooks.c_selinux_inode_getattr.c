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
 int /*<<< orphan*/  FILE__GETATTR ; 
 int /*<<< orphan*/  current_cred () ; 
 int path_has_perm (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_getattr(const struct path *path)
{
	return path_has_perm(current_cred(), path, FILE__GETATTR);
}