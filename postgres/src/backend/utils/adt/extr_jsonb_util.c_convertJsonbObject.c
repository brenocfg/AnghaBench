#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_18__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_14__ {int nPairs; TYPE_5__* pairs; } ;
struct TYPE_15__ {TYPE_1__ object; } ;
struct TYPE_17__ {TYPE_2__ val; } ;
struct TYPE_16__ {int len; } ;
typedef  TYPE_3__* StringInfo ;
typedef  TYPE_4__ JsonbValue ;
typedef  TYPE_5__ JsonbPair ;
typedef  int JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int JBE_OFFLENFLD (int) ; 
 int JB_FOBJECT ; 
 int JB_OFFSET_STRIDE ; 
 int JENTRY_HAS_OFF ; 
 int JENTRY_ISCONTAINER ; 
 int JENTRY_OFFLENMASK ; 
 int JENTRY_TYPEMASK ; 
 int /*<<< orphan*/  appendToBuffer (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  convertJsonbScalar (TYPE_3__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convertJsonbValue (TYPE_3__*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copyToBuffer (TYPE_3__*,int,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int /*<<< orphan*/  padBufferToInt (TYPE_3__*) ; 
 int reserveFromBuffer (TYPE_3__*,int) ; 

__attribute__((used)) static void
convertJsonbObject(StringInfo buffer, JEntry *pheader, JsonbValue *val, int level)
{
	int			base_offset;
	int			jentry_offset;
	int			i;
	int			totallen;
	uint32		header;
	int			nPairs = val->val.object.nPairs;

	/* Remember where in the buffer this object starts. */
	base_offset = buffer->len;

	/* Align to 4-byte boundary (any padding counts as part of my data) */
	padBufferToInt(buffer);

	/*
	 * Construct the header Jentry and store it in the beginning of the
	 * variable-length payload.
	 */
	header = nPairs | JB_FOBJECT;
	appendToBuffer(buffer, (char *) &header, sizeof(uint32));

	/* Reserve space for the JEntries of the keys and values. */
	jentry_offset = reserveFromBuffer(buffer, sizeof(JEntry) * nPairs * 2);

	/*
	 * Iterate over the keys, then over the values, since that is the ordering
	 * we want in the on-disk representation.
	 */
	totallen = 0;
	for (i = 0; i < nPairs; i++)
	{
		JsonbPair  *pair = &val->val.object.pairs[i];
		int			len;
		JEntry		meta;

		/*
		 * Convert key, producing a JEntry and appending its variable-length
		 * data to buffer
		 */
		convertJsonbScalar(buffer, &meta, &pair->key);

		len = JBE_OFFLENFLD(meta);
		totallen += len;

		/*
		 * Bail out if total variable-length data exceeds what will fit in a
		 * JEntry length field.  We check this in each iteration, not just
		 * once at the end, to forestall possible integer overflow.
		 */
		if (totallen > JENTRY_OFFLENMASK)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("total size of jsonb object elements exceeds the maximum of %u bytes",
							JENTRY_OFFLENMASK)));

		/*
		 * Convert each JB_OFFSET_STRIDE'th length to an offset.
		 */
		if ((i % JB_OFFSET_STRIDE) == 0)
			meta = (meta & JENTRY_TYPEMASK) | totallen | JENTRY_HAS_OFF;

		copyToBuffer(buffer, jentry_offset, (char *) &meta, sizeof(JEntry));
		jentry_offset += sizeof(JEntry);
	}
	for (i = 0; i < nPairs; i++)
	{
		JsonbPair  *pair = &val->val.object.pairs[i];
		int			len;
		JEntry		meta;

		/*
		 * Convert value, producing a JEntry and appending its variable-length
		 * data to buffer
		 */
		convertJsonbValue(buffer, &meta, &pair->value, level + 1);

		len = JBE_OFFLENFLD(meta);
		totallen += len;

		/*
		 * Bail out if total variable-length data exceeds what will fit in a
		 * JEntry length field.  We check this in each iteration, not just
		 * once at the end, to forestall possible integer overflow.
		 */
		if (totallen > JENTRY_OFFLENMASK)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("total size of jsonb object elements exceeds the maximum of %u bytes",
							JENTRY_OFFLENMASK)));

		/*
		 * Convert each JB_OFFSET_STRIDE'th length to an offset.
		 */
		if (((i + nPairs) % JB_OFFSET_STRIDE) == 0)
			meta = (meta & JENTRY_TYPEMASK) | totallen | JENTRY_HAS_OFF;

		copyToBuffer(buffer, jentry_offset, (char *) &meta, sizeof(JEntry));
		jentry_offset += sizeof(JEntry);
	}

	/* Total data size is everything we've appended to buffer */
	totallen = buffer->len - base_offset;

	/* Check length again, since we didn't include the metadata above */
	if (totallen > JENTRY_OFFLENMASK)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("total size of jsonb object elements exceeds the maximum of %u bytes",
						JENTRY_OFFLENMASK)));

	/* Initialize the header of this node in the container's JEntry array */
	*pheader = JENTRY_ISCONTAINER | totallen;
}