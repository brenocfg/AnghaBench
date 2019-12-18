#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  relopt_gen ;
struct TYPE_11__ {scalar_t__ name; void* namelen; int /*<<< orphan*/  type; int /*<<< orphan*/  lockmode; } ;
struct TYPE_15__ {TYPE_2__ gen; } ;
struct TYPE_14__ {TYPE_2__ gen; } ;
struct TYPE_13__ {TYPE_2__ gen; } ;
struct TYPE_12__ {TYPE_2__ gen; } ;
struct TYPE_10__ {TYPE_2__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoLockModesConflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RELOPT_TYPE_BOOL ; 
 int /*<<< orphan*/  RELOPT_TYPE_ENUM ; 
 int /*<<< orphan*/  RELOPT_TYPE_INT ; 
 int /*<<< orphan*/  RELOPT_TYPE_REAL ; 
 int /*<<< orphan*/  RELOPT_TYPE_STRING ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 TYPE_8__* boolRelOpts ; 
 TYPE_2__** custom_options ; 
 TYPE_6__* enumRelOpts ; 
 TYPE_5__* intRelOpts ; 
 int need_initialization ; 
 int num_custom_options ; 
 int /*<<< orphan*/  pfree (TYPE_2__**) ; 
 TYPE_3__* realRelOpts ; 
 TYPE_2__** relOpts ; 
 TYPE_1__* stringRelOpts ; 
 void* strlen (scalar_t__) ; 

__attribute__((used)) static void
initialize_reloptions(void)
{
	int			i;
	int			j;

	j = 0;
	for (i = 0; boolRelOpts[i].gen.name; i++)
	{
		Assert(DoLockModesConflict(boolRelOpts[i].gen.lockmode,
								   boolRelOpts[i].gen.lockmode));
		j++;
	}
	for (i = 0; intRelOpts[i].gen.name; i++)
	{
		Assert(DoLockModesConflict(intRelOpts[i].gen.lockmode,
								   intRelOpts[i].gen.lockmode));
		j++;
	}
	for (i = 0; realRelOpts[i].gen.name; i++)
	{
		Assert(DoLockModesConflict(realRelOpts[i].gen.lockmode,
								   realRelOpts[i].gen.lockmode));
		j++;
	}
	for (i = 0; enumRelOpts[i].gen.name; i++)
	{
		Assert(DoLockModesConflict(enumRelOpts[i].gen.lockmode,
								   enumRelOpts[i].gen.lockmode));
		j++;
	}
	for (i = 0; stringRelOpts[i].gen.name; i++)
	{
		Assert(DoLockModesConflict(stringRelOpts[i].gen.lockmode,
								   stringRelOpts[i].gen.lockmode));
		j++;
	}
	j += num_custom_options;

	if (relOpts)
		pfree(relOpts);
	relOpts = MemoryContextAlloc(TopMemoryContext,
								 (j + 1) * sizeof(relopt_gen *));

	j = 0;
	for (i = 0; boolRelOpts[i].gen.name; i++)
	{
		relOpts[j] = &boolRelOpts[i].gen;
		relOpts[j]->type = RELOPT_TYPE_BOOL;
		relOpts[j]->namelen = strlen(relOpts[j]->name);
		j++;
	}

	for (i = 0; intRelOpts[i].gen.name; i++)
	{
		relOpts[j] = &intRelOpts[i].gen;
		relOpts[j]->type = RELOPT_TYPE_INT;
		relOpts[j]->namelen = strlen(relOpts[j]->name);
		j++;
	}

	for (i = 0; realRelOpts[i].gen.name; i++)
	{
		relOpts[j] = &realRelOpts[i].gen;
		relOpts[j]->type = RELOPT_TYPE_REAL;
		relOpts[j]->namelen = strlen(relOpts[j]->name);
		j++;
	}

	for (i = 0; enumRelOpts[i].gen.name; i++)
	{
		relOpts[j] = &enumRelOpts[i].gen;
		relOpts[j]->type = RELOPT_TYPE_ENUM;
		relOpts[j]->namelen = strlen(relOpts[j]->name);
		j++;
	}

	for (i = 0; stringRelOpts[i].gen.name; i++)
	{
		relOpts[j] = &stringRelOpts[i].gen;
		relOpts[j]->type = RELOPT_TYPE_STRING;
		relOpts[j]->namelen = strlen(relOpts[j]->name);
		j++;
	}

	for (i = 0; i < num_custom_options; i++)
	{
		relOpts[j] = custom_options[i];
		j++;
	}

	/* add a list terminator */
	relOpts[j] = NULL;

	/* flag the work is complete */
	need_initialization = false;
}