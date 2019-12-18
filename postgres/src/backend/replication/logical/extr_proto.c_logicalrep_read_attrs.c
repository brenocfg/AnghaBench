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
typedef  int uint8 ;
struct TYPE_3__ {char** attnames; int natts; int /*<<< orphan*/ * attkeys; scalar_t__* atttyps; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ LogicalRepRelation ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int LOGICALREP_IS_REPLICA_IDENTITY ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int) ; 
 void* palloc (int) ; 
 int pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_getmsgstring (int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logicalrep_read_attrs(StringInfo in, LogicalRepRelation *rel)
{
	int			i;
	int			natts;
	char	  **attnames;
	Oid		   *atttyps;
	Bitmapset  *attkeys = NULL;

	natts = pq_getmsgint(in, 2);
	attnames = palloc(natts * sizeof(char *));
	atttyps = palloc(natts * sizeof(Oid));

	/* read the attributes */
	for (i = 0; i < natts; i++)
	{
		uint8		flags;

		/* Check for replica identity column */
		flags = pq_getmsgbyte(in);
		if (flags & LOGICALREP_IS_REPLICA_IDENTITY)
			attkeys = bms_add_member(attkeys, i);

		/* attribute name */
		attnames[i] = pstrdup(pq_getmsgstring(in));

		/* attribute type id */
		atttyps[i] = (Oid) pq_getmsgint(in, 4);

		/* we ignore attribute mode for now */
		(void) pq_getmsgint(in, 4);
	}

	rel->attnames = attnames;
	rel->atttyps = atttyps;
	rel->attkeys = attkeys;
	rel->natts = natts;
}