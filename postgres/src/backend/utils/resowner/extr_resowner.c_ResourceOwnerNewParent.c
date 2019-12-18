#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* nextchild; struct TYPE_4__* parent; struct TYPE_4__* firstchild; } ;
typedef  TYPE_1__* ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

void
ResourceOwnerNewParent(ResourceOwner owner,
					   ResourceOwner newparent)
{
	ResourceOwner oldparent = owner->parent;

	if (oldparent)
	{
		if (owner == oldparent->firstchild)
			oldparent->firstchild = owner->nextchild;
		else
		{
			ResourceOwner child;

			for (child = oldparent->firstchild; child; child = child->nextchild)
			{
				if (owner == child->nextchild)
				{
					child->nextchild = owner->nextchild;
					break;
				}
			}
		}
	}

	if (newparent)
	{
		Assert(owner != newparent);
		owner->parent = newparent;
		owner->nextchild = newparent->firstchild;
		newparent->firstchild = owner;
	}
	else
	{
		owner->parent = NULL;
		owner->nextchild = NULL;
	}
}