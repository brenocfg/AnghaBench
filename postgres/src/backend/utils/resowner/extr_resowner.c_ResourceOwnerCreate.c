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
struct TYPE_4__ {char const* name; int /*<<< orphan*/  jitarr; int /*<<< orphan*/  dsmarr; int /*<<< orphan*/  filearr; int /*<<< orphan*/  snapshotarr; int /*<<< orphan*/  tupdescarr; int /*<<< orphan*/  planrefarr; int /*<<< orphan*/  relrefarr; int /*<<< orphan*/  catlistrefarr; int /*<<< orphan*/  catrefarr; int /*<<< orphan*/  bufferarr; struct TYPE_4__* firstchild; struct TYPE_4__* nextchild; struct TYPE_4__* parent; } ;
typedef  int /*<<< orphan*/  ResourceOwnerData ;
typedef  TYPE_1__* ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileGetDatum (int) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceArrayInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 

ResourceOwner
ResourceOwnerCreate(ResourceOwner parent, const char *name)
{
	ResourceOwner owner;

	owner = (ResourceOwner) MemoryContextAllocZero(TopMemoryContext,
												   sizeof(ResourceOwnerData));
	owner->name = name;

	if (parent)
	{
		owner->parent = parent;
		owner->nextchild = parent->firstchild;
		parent->firstchild = owner;
	}

	ResourceArrayInit(&(owner->bufferarr), BufferGetDatum(InvalidBuffer));
	ResourceArrayInit(&(owner->catrefarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->catlistrefarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->relrefarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->planrefarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->tupdescarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->snapshotarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->filearr), FileGetDatum(-1));
	ResourceArrayInit(&(owner->dsmarr), PointerGetDatum(NULL));
	ResourceArrayInit(&(owner->jitarr), PointerGetDatum(NULL));

	return owner;
}