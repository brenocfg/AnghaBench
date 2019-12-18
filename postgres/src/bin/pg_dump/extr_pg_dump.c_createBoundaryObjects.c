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
struct TYPE_4__ {void* name; void* catId; int /*<<< orphan*/  objType; } ;
typedef  TYPE_1__ DumpableObject ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_1__*) ; 
 int /*<<< orphan*/  DO_POST_DATA_BOUNDARY ; 
 int /*<<< orphan*/  DO_PRE_DATA_BOUNDARY ; 
 void* nilCatalogId ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (char*) ; 

__attribute__((used)) static DumpableObject *
createBoundaryObjects(void)
{
	DumpableObject *dobjs;

	dobjs = (DumpableObject *) pg_malloc(2 * sizeof(DumpableObject));

	dobjs[0].objType = DO_PRE_DATA_BOUNDARY;
	dobjs[0].catId = nilCatalogId;
	AssignDumpId(dobjs + 0);
	dobjs[0].name = pg_strdup("PRE-DATA BOUNDARY");

	dobjs[1].objType = DO_POST_DATA_BOUNDARY;
	dobjs[1].catId = nilCatalogId;
	AssignDumpId(dobjs + 1);
	dobjs[1].name = pg_strdup("POST-DATA BOUNDARY");

	return dobjs;
}