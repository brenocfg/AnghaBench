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
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_4__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  RI_QueryKey ;
typedef  int /*<<< orphan*/  RI_QueryHashEntry ;
typedef  int /*<<< orphan*/  RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  RI_CompareKey ;
typedef  int /*<<< orphan*/  RI_CompareHashEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  InvalidateConstraintCacheCallBack ; 
 int /*<<< orphan*/  RI_INIT_CONSTRAINTHASHSIZE ; 
 int /*<<< orphan*/  RI_INIT_QUERYHASHSIZE ; 
 void* hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* ri_compare_cache ; 
 void* ri_constraint_cache ; 
 void* ri_query_cache ; 

__attribute__((used)) static void
ri_InitHashTables(void)
{
	HASHCTL		ctl;

	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(Oid);
	ctl.entrysize = sizeof(RI_ConstraintInfo);
	ri_constraint_cache = hash_create("RI constraint cache",
									  RI_INIT_CONSTRAINTHASHSIZE,
									  &ctl, HASH_ELEM | HASH_BLOBS);

	/* Arrange to flush cache on pg_constraint changes */
	CacheRegisterSyscacheCallback(CONSTROID,
								  InvalidateConstraintCacheCallBack,
								  (Datum) 0);

	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(RI_QueryKey);
	ctl.entrysize = sizeof(RI_QueryHashEntry);
	ri_query_cache = hash_create("RI query cache",
								 RI_INIT_QUERYHASHSIZE,
								 &ctl, HASH_ELEM | HASH_BLOBS);

	memset(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(RI_CompareKey);
	ctl.entrysize = sizeof(RI_CompareHashEntry);
	ri_compare_cache = hash_create("RI compare cache",
								   RI_INIT_QUERYHASHSIZE,
								   &ctl, HASH_ELEM | HASH_BLOBS);
}