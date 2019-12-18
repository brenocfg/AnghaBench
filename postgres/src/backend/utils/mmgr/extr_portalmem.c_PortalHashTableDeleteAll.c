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
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {TYPE_2__* portal; } ;
typedef  TYPE_1__ PortalHashEnt ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 scalar_t__ PORTAL_ACTIVE ; 
 int /*<<< orphan*/  PortalDrop (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * PortalHashTable ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

void
PortalHashTableDeleteAll(void)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	if (PortalHashTable == NULL)
		return;

	hash_seq_init(&status, PortalHashTable);
	while ((hentry = hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		/* Can't close the active portal (the one running the command) */
		if (portal->status == PORTAL_ACTIVE)
			continue;

		PortalDrop(portal, false);

		/* Restart the iteration in case that led to other drops */
		hash_seq_term(&status);
		hash_seq_init(&status, PortalHashTable);
	}
}