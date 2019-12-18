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
struct TYPE_3__ {int nlocks; int /*<<< orphan*/  name; int /*<<< orphan*/ ** locks; } ;
typedef  TYPE_1__* ResourceOwner ;
typedef  int /*<<< orphan*/  LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int MAX_RESOWNER_LOCKS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ResourceOwnerForgetLock(ResourceOwner owner, LOCALLOCK *locallock)
{
	int			i;

	if (owner->nlocks > MAX_RESOWNER_LOCKS)
		return;					/* we have overflowed */

	Assert(owner->nlocks > 0);
	for (i = owner->nlocks - 1; i >= 0; i--)
	{
		if (locallock == owner->locks[i])
		{
			owner->locks[i] = owner->locks[owner->nlocks - 1];
			owner->nlocks--;
			return;
		}
	}
	elog(ERROR, "lock reference %p is not owned by resource owner %s",
		 locallock, owner->name);
}