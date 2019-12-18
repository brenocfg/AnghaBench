#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint16 ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_14__ {int atttypmod; scalar_t__ atttypid; int /*<<< orphan*/  attname; scalar_t__ attnum; scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {int natts; } ;
struct TYPE_11__ {scalar_t__ relreplident; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/  INDEX_ATTR_BITMAP_IDENTITY_KEY ; 
 int /*<<< orphan*/  LOGICALREP_IS_REPLICA_IDENTITY ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/ * RelationGetIndexAttrBitmap (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_member (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logicalrep_write_attrs(StringInfo out, Relation rel)
{
	TupleDesc	desc;
	int			i;
	uint16		nliveatts = 0;
	Bitmapset  *idattrs = NULL;
	bool		replidentfull;

	desc = RelationGetDescr(rel);

	/* send number of live attributes */
	for (i = 0; i < desc->natts; i++)
	{
		if (TupleDescAttr(desc, i)->attisdropped || TupleDescAttr(desc, i)->attgenerated)
			continue;
		nliveatts++;
	}
	pq_sendint16(out, nliveatts);

	/* fetch bitmap of REPLICATION IDENTITY attributes */
	replidentfull = (rel->rd_rel->relreplident == REPLICA_IDENTITY_FULL);
	if (!replidentfull)
		idattrs = RelationGetIndexAttrBitmap(rel,
											 INDEX_ATTR_BITMAP_IDENTITY_KEY);

	/* send the attributes */
	for (i = 0; i < desc->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(desc, i);
		uint8		flags = 0;

		if (att->attisdropped || att->attgenerated)
			continue;

		/* REPLICA IDENTITY FULL means all columns are sent as part of key. */
		if (replidentfull ||
			bms_is_member(att->attnum - FirstLowInvalidHeapAttributeNumber,
						  idattrs))
			flags |= LOGICALREP_IS_REPLICA_IDENTITY;

		pq_sendbyte(out, flags);

		/* attribute name */
		pq_sendstring(out, NameStr(att->attname));

		/* attribute type id */
		pq_sendint32(out, (int) att->atttypid);

		/* attribute mode */
		pq_sendint32(out, att->atttypmod);
	}

	bms_free(idattrs);
}