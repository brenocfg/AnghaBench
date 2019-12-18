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
struct TYPE_3__ {size_t nlocks; int /*<<< orphan*/ ** locks; } ;
typedef  TYPE_1__* ResourceOwner ;
typedef  int /*<<< orphan*/  LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 size_t MAX_RESOWNER_LOCKS ; 

void
ResourceOwnerRememberLock(ResourceOwner owner, LOCALLOCK *locallock)
{
	Assert(locallock != NULL);

	if (owner->nlocks > MAX_RESOWNER_LOCKS)
		return;					/* we have already overflowed */

	if (owner->nlocks < MAX_RESOWNER_LOCKS)
		owner->locks[owner->nlocks] = locallock;
	else
	{
		/* overflowed */
	}
	owner->nlocks++;
}