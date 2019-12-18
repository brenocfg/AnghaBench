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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {int isvalid; } ;
typedef  TYPE_1__ TSAnyCacheEntry ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * TSConfigCacheHash ; 
 int /*<<< orphan*/  TSCurrentConfigCache ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
InvalidateTSCacheCallBack(Datum arg, int cacheid, uint32 hashvalue)
{
	HTAB	   *hash = (HTAB *) DatumGetPointer(arg);
	HASH_SEQ_STATUS status;
	TSAnyCacheEntry *entry;

	hash_seq_init(&status, hash);
	while ((entry = (TSAnyCacheEntry *) hash_seq_search(&status)) != NULL)
		entry->isvalid = false;

	/* Also invalidate the current-config cache if it's pg_ts_config */
	if (hash == TSConfigCacheHash)
		TSCurrentConfigCache = InvalidOid;
}