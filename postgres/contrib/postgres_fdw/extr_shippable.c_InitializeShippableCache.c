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
typedef  int /*<<< orphan*/  ShippableCacheKey ;
typedef  int /*<<< orphan*/  ShippableCacheEntry ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOREIGNSERVEROID ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  InvalidateShippableCacheCallback ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShippableCacheHash ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static void
InitializeShippableCache(void)
{
	HASHCTL		ctl;

	/* Create the hash table. */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(ShippableCacheKey);
	ctl.entrysize = sizeof(ShippableCacheEntry);
	ShippableCacheHash =
		hash_create("Shippability cache", 256, &ctl, HASH_ELEM | HASH_BLOBS);

	/* Set up invalidation callback on pg_foreign_server. */
	CacheRegisterSyscacheCallback(FOREIGNSERVEROID,
								  InvalidateShippableCacheCallback,
								  (Datum) 0);
}