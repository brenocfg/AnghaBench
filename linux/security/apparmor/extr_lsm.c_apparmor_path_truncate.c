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
 int AA_MAY_SETATTR ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  OP_TRUNC ; 
 int common_perm_cond (int /*<<< orphan*/ ,struct path const*,int) ; 

__attribute__((used)) static int apparmor_path_truncate(const struct path *path)
{
	return common_perm_cond(OP_TRUNC, path, MAY_WRITE | AA_MAY_SETATTR);
}