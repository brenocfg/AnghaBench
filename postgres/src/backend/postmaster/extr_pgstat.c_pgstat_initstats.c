#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ t_id; } ;
struct TYPE_6__ {scalar_t__ rd_id; TYPE_1__* rd_rel; TYPE_4__* pgstat_info; } ;
struct TYPE_5__ {char relkind; int /*<<< orphan*/  relisshared; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ PGINVALID_SOCKET ; 
 char RELKIND_INDEX ; 
 char RELKIND_MATVIEW ; 
 char RELKIND_RELATION ; 
 char RELKIND_SEQUENCE ; 
 char RELKIND_TOASTVALUE ; 
 TYPE_4__* get_tabstat_entry (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pgStatSock ; 
 int /*<<< orphan*/  pgstat_track_counts ; 

void
pgstat_initstats(Relation rel)
{
	Oid			rel_id = rel->rd_id;
	char		relkind = rel->rd_rel->relkind;

	/* We only count stats for things that have storage */
	if (!(relkind == RELKIND_RELATION ||
		  relkind == RELKIND_MATVIEW ||
		  relkind == RELKIND_INDEX ||
		  relkind == RELKIND_TOASTVALUE ||
		  relkind == RELKIND_SEQUENCE))
	{
		rel->pgstat_info = NULL;
		return;
	}

	if (pgStatSock == PGINVALID_SOCKET || !pgstat_track_counts)
	{
		/* We're not counting at all */
		rel->pgstat_info = NULL;
		return;
	}

	/*
	 * If we already set up this relation in the current transaction, nothing
	 * to do.
	 */
	if (rel->pgstat_info != NULL &&
		rel->pgstat_info->t_id == rel_id)
		return;

	/* Else find or make the PgStat_TableStatus entry, and update link */
	rel->pgstat_info = get_tabstat_entry(rel_id, rel->rd_rel->relisshared);
}