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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  flags; struct TYPE_3__* nextDomain; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  TCFLAGS_CHECKED_DOMAIN_CONSTRAINTS ; 
 TYPE_1__* firstDomainTypeEntry ; 

__attribute__((used)) static void
TypeCacheConstrCallback(Datum arg, int cacheid, uint32 hashvalue)
{
	TypeCacheEntry *typentry;

	/*
	 * Because this is called very frequently, and typically very few of the
	 * typcache entries are for domains, we don't use hash_seq_search here.
	 * Instead we thread all the domain-type entries together so that we can
	 * visit them cheaply.
	 */
	for (typentry = firstDomainTypeEntry;
		 typentry != NULL;
		 typentry = typentry->nextDomain)
	{
		/* Reset domain constraint validity information */
		typentry->flags &= ~TCFLAGS_CHECKED_DOMAIN_CONSTRAINTS;
	}
}