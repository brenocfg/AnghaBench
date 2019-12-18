#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parentMap; } ;
struct TYPE_5__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  int /*<<< orphan*/  ParentMapEntry ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_2__ GISTBuildState ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static void
gistInitParentMap(GISTBuildState *buildstate)
{
	HASHCTL		hashCtl;

	hashCtl.keysize = sizeof(BlockNumber);
	hashCtl.entrysize = sizeof(ParentMapEntry);
	hashCtl.hcxt = CurrentMemoryContext;
	buildstate->parentMap = hash_create("gistbuild parent map",
										1024,
										&hashCtl,
										HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
}