#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int trancheId; char* trancheName; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int,char*) ; 
 char const** LWLockTrancheArray ; 
 int LWLockTranchesAllocated ; 
 int LWTRANCHE_BUFFER_MAPPING ; 
 int LWTRANCHE_FIRST_USER_DEFINED ; 
 int LWTRANCHE_LOCK_MANAGER ; 
 int LWTRANCHE_PARALLEL_APPEND ; 
 int LWTRANCHE_PARALLEL_HASH_JOIN ; 
 int LWTRANCHE_PARALLEL_QUERY_DSA ; 
 int LWTRANCHE_PREDICATE_LOCK_MANAGER ; 
 int LWTRANCHE_SESSION_DSA ; 
 int LWTRANCHE_SESSION_RECORD_TABLE ; 
 int LWTRANCHE_SESSION_TYPMOD_TABLE ; 
 int LWTRANCHE_SHARED_TUPLESTORE ; 
 int LWTRANCHE_SXACT ; 
 int LWTRANCHE_TBM ; 
 char** MainLWLockNames ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int NUM_INDIVIDUAL_LWLOCKS ; 
 TYPE_1__* NamedLWLockTrancheArray ; 
 int NamedLWLockTrancheRequests ; 
 int /*<<< orphan*/  TopMemoryContext ; 

__attribute__((used)) static void
RegisterLWLockTranches(void)
{
	int			i;

	if (LWLockTrancheArray == NULL)
	{
		LWLockTranchesAllocated = 128;
		LWLockTrancheArray = (const char **)
			MemoryContextAllocZero(TopMemoryContext,
								   LWLockTranchesAllocated * sizeof(char *));
		Assert(LWLockTranchesAllocated >= LWTRANCHE_FIRST_USER_DEFINED);
	}

	for (i = 0; i < NUM_INDIVIDUAL_LWLOCKS; ++i)
		LWLockRegisterTranche(i, MainLWLockNames[i]);

	LWLockRegisterTranche(LWTRANCHE_BUFFER_MAPPING, "buffer_mapping");
	LWLockRegisterTranche(LWTRANCHE_LOCK_MANAGER, "lock_manager");
	LWLockRegisterTranche(LWTRANCHE_PREDICATE_LOCK_MANAGER,
						  "predicate_lock_manager");
	LWLockRegisterTranche(LWTRANCHE_PARALLEL_QUERY_DSA,
						  "parallel_query_dsa");
	LWLockRegisterTranche(LWTRANCHE_SESSION_DSA,
						  "session_dsa");
	LWLockRegisterTranche(LWTRANCHE_SESSION_RECORD_TABLE,
						  "session_record_table");
	LWLockRegisterTranche(LWTRANCHE_SESSION_TYPMOD_TABLE,
						  "session_typmod_table");
	LWLockRegisterTranche(LWTRANCHE_SHARED_TUPLESTORE,
						  "shared_tuplestore");
	LWLockRegisterTranche(LWTRANCHE_TBM, "tbm");
	LWLockRegisterTranche(LWTRANCHE_PARALLEL_APPEND, "parallel_append");
	LWLockRegisterTranche(LWTRANCHE_PARALLEL_HASH_JOIN, "parallel_hash_join");
	LWLockRegisterTranche(LWTRANCHE_SXACT, "serializable_xact");

	/* Register named tranches. */
	for (i = 0; i < NamedLWLockTrancheRequests; i++)
		LWLockRegisterTranche(NamedLWLockTrancheArray[i].trancheId,
							  NamedLWLockTrancheArray[i].trancheName);
}