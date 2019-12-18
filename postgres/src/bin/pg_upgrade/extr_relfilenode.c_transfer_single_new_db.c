#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cat_ver; } ;
struct TYPE_12__ {TYPE_2__ controldata; } ;
struct TYPE_8__ {scalar_t__ cat_ver; } ;
struct TYPE_11__ {int /*<<< orphan*/  major_version; TYPE_1__ controldata; } ;
struct TYPE_10__ {int /*<<< orphan*/  old_tablespace; } ;
typedef  TYPE_3__ FileNameMap ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ VISIBILITY_MAP_CRASHSAFE_CAT_VER ; 
 scalar_t__ VISIBILITY_MAP_FROZEN_BIT_CAT_VER ; 
 TYPE_7__ new_cluster ; 
 TYPE_6__ old_cluster ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transfer_relfile (TYPE_3__*,char*,int) ; 

__attribute__((used)) static void
transfer_single_new_db(FileNameMap *maps, int size, char *old_tablespace)
{
	int			mapnum;
	bool		vm_crashsafe_match = true;
	bool		vm_must_add_frozenbit = false;

	/*
	 * Do the old and new cluster disagree on the crash-safetiness of the vm
	 * files?  If so, do not copy them.
	 */
	if (old_cluster.controldata.cat_ver < VISIBILITY_MAP_CRASHSAFE_CAT_VER &&
		new_cluster.controldata.cat_ver >= VISIBILITY_MAP_CRASHSAFE_CAT_VER)
		vm_crashsafe_match = false;

	/*
	 * Do we need to rewrite visibilitymap?
	 */
	if (old_cluster.controldata.cat_ver < VISIBILITY_MAP_FROZEN_BIT_CAT_VER &&
		new_cluster.controldata.cat_ver >= VISIBILITY_MAP_FROZEN_BIT_CAT_VER)
		vm_must_add_frozenbit = true;

	for (mapnum = 0; mapnum < size; mapnum++)
	{
		if (old_tablespace == NULL ||
			strcmp(maps[mapnum].old_tablespace, old_tablespace) == 0)
		{
			/* transfer primary file */
			transfer_relfile(&maps[mapnum], "", vm_must_add_frozenbit);

			/* fsm/vm files added in PG 8.4 */
			if (GET_MAJOR_VERSION(old_cluster.major_version) >= 804)
			{
				/*
				 * Copy/link any fsm and vm files, if they exist
				 */
				transfer_relfile(&maps[mapnum], "_fsm", vm_must_add_frozenbit);
				if (vm_crashsafe_match)
					transfer_relfile(&maps[mapnum], "_vm", vm_must_add_frozenbit);
			}
		}
	}
}