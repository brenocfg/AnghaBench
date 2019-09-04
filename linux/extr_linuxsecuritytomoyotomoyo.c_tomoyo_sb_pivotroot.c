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
 int /*<<< orphan*/  TOMOYO_TYPE_PIVOT_ROOT ; 
 int tomoyo_path2_perm (int /*<<< orphan*/ ,struct path const*,struct path const*) ; 

__attribute__((used)) static int tomoyo_sb_pivotroot(const struct path *old_path, const struct path *new_path)
{
	return tomoyo_path2_perm(TOMOYO_TYPE_PIVOT_ROOT, new_path, old_path);
}