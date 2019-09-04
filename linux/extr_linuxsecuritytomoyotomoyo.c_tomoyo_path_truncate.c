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
 int /*<<< orphan*/  TOMOYO_TYPE_TRUNCATE ; 
 int tomoyo_path_perm (int /*<<< orphan*/ ,struct path const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tomoyo_path_truncate(const struct path *path)
{
	return tomoyo_path_perm(TOMOYO_TYPE_TRUNCATE, path, NULL);
}