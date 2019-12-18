#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_19__ {int /*<<< orphan*/  rel; } ;
struct TYPE_18__ {int attlen; scalar_t__ attbyval; int /*<<< orphan*/  attnum; } ;
struct TYPE_17__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_16__ {int natts; } ;
typedef  TYPE_2__* IndexTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ BtreeCheckState ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  IndexTupleHasVarwidths (TYPE_2__*) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ VARATT_IS_COMPRESSED (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* index_form_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  index_getattr (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IndexTuple
bt_normalize_tuple(BtreeCheckState *state, IndexTuple itup)
{
	TupleDesc	tupleDescriptor = RelationGetDescr(state->rel);
	Datum		normalized[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	bool		toast_free[INDEX_MAX_KEYS];
	bool		formnewtup = false;
	IndexTuple	reformed;
	int			i;

	/* Easy case: It's immediately clear that tuple has no varlena datums */
	if (!IndexTupleHasVarwidths(itup))
		return itup;

	for (i = 0; i < tupleDescriptor->natts; i++)
	{
		Form_pg_attribute att;

		att = TupleDescAttr(tupleDescriptor, i);

		/* Assume untoasted/already normalized datum initially */
		toast_free[i] = false;
		normalized[i] = index_getattr(itup, att->attnum,
									  tupleDescriptor,
									  &isnull[i]);
		if (att->attbyval || att->attlen != -1 || isnull[i])
			continue;

		/*
		 * Callers always pass a tuple that could safely be inserted into the
		 * index without further processing, so an external varlena header
		 * should never be encountered here
		 */
		if (VARATT_IS_EXTERNAL(DatumGetPointer(normalized[i])))
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("external varlena datum in tuple that references heap row (%u,%u) in index \"%s\"",
							ItemPointerGetBlockNumber(&(itup->t_tid)),
							ItemPointerGetOffsetNumber(&(itup->t_tid)),
							RelationGetRelationName(state->rel))));
		else if (VARATT_IS_COMPRESSED(DatumGetPointer(normalized[i])))
		{
			formnewtup = true;
			normalized[i] = PointerGetDatum(PG_DETOAST_DATUM(normalized[i]));
			toast_free[i] = true;
		}
	}

	/* Easier case: Tuple has varlena datums, none of which are compressed */
	if (!formnewtup)
		return itup;

	/*
	 * Hard case: Tuple had compressed varlena datums that necessitate
	 * creating normalized version of the tuple from uncompressed input datums
	 * (normalized input datums).  This is rather naive, but shouldn't be
	 * necessary too often.
	 *
	 * Note that we rely on deterministic index_form_tuple() TOAST compression
	 * of normalized input.
	 */
	reformed = index_form_tuple(tupleDescriptor, normalized, isnull);
	reformed->t_tid = itup->t_tid;

	/* Cannot leak memory here */
	for (i = 0; i < tupleDescriptor->natts; i++)
		if (toast_free[i])
			pfree(DatumGetPointer(normalized[i]));

	return reformed;
}