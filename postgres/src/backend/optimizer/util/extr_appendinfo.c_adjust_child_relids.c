#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  child_relid; int /*<<< orphan*/  parent_relid; } ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  TYPE_1__ AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_del_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bms_is_member (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Relids
adjust_child_relids(Relids relids, int nappinfos, AppendRelInfo **appinfos)
{
	Bitmapset  *result = NULL;
	int			cnt;

	for (cnt = 0; cnt < nappinfos; cnt++)
	{
		AppendRelInfo *appinfo = appinfos[cnt];

		/* Remove parent, add child */
		if (bms_is_member(appinfo->parent_relid, relids))
		{
			/* Make a copy if we are changing the set. */
			if (!result)
				result = bms_copy(relids);

			result = bms_del_member(result, appinfo->parent_relid);
			result = bms_add_member(result, appinfo->child_relid);
		}
	}

	/* If we made any changes, return the modified copy. */
	if (result)
		return result;

	/* Otherwise, return the original set without modification. */
	return relids;
}