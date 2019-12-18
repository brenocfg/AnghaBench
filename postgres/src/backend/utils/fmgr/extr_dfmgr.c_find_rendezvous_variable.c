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
struct TYPE_5__ {void* varValue; } ;
typedef  TYPE_1__ rendezvousHashEntry ;
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_6__ {int entrysize; int /*<<< orphan*/  keysize; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int*) ; 

void	  **
find_rendezvous_variable(const char *varName)
{
	static HTAB *rendezvousHash = NULL;

	rendezvousHashEntry *hentry;
	bool		found;

	/* Create a hashtable if we haven't already done so in this process */
	if (rendezvousHash == NULL)
	{
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = NAMEDATALEN;
		ctl.entrysize = sizeof(rendezvousHashEntry);
		rendezvousHash = hash_create("Rendezvous variable hash",
									 16,
									 &ctl,
									 HASH_ELEM);
	}

	/* Find or create the hashtable entry for this varName */
	hentry = (rendezvousHashEntry *) hash_search(rendezvousHash,
												 varName,
												 HASH_ENTER,
												 &found);

	/* Initialize to NULL if first time */
	if (!found)
		hentry->varValue = NULL;

	return &hentry->varValue;
}