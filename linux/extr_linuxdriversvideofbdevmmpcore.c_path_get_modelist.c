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
struct mmp_path {TYPE_1__* panel; } ;
struct mmp_mode {int dummy; } ;
struct TYPE_2__ {int (* get_modelist ) (TYPE_1__*,struct mmp_mode**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (TYPE_1__*,struct mmp_mode**) ; 

__attribute__((used)) static int path_get_modelist(struct mmp_path *path,
		struct mmp_mode **modelist)
{
	BUG_ON(!path || !modelist);

	if (path->panel && path->panel->get_modelist)
		return path->panel->get_modelist(path->panel, modelist);

	return 0;
}