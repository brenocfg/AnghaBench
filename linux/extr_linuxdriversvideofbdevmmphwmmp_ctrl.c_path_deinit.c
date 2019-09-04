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
struct mmphw_path_plat {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmp_unregister_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_deinit(struct mmphw_path_plat *path_plat)
{
	if (!path_plat)
		return;

	mmp_unregister_path(path_plat->path);
}