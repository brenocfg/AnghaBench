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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int sk_attno; int sk_flags; int sk_strategy; int /*<<< orphan*/  sk_argument; int /*<<< orphan*/  sk_collation; int /*<<< orphan*/  sk_func; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  BTGreaterEqualStrategyNumber 131 
#define  BTGreaterStrategyNumber 130 
#define  BTLessEqualStrategyNumber 129 
#define  BTLessStrategyNumber 128 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVERT_COMPARE_RESULT (scalar_t__) ; 
 int SK_BT_DESC ; 
 int SK_BT_NULLS_FIRST ; 
 int SK_BT_REQBKWD ; 
 int SK_BT_REQFWD ; 
 int SK_ISNULL ; 
 int SK_ROW_END ; 
 int SK_ROW_MEMBER ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
_bt_check_rowcompare(ScanKey skey, IndexTuple tuple, int tupnatts,
					 TupleDesc tupdesc, ScanDirection dir, bool *continuescan)
{
	ScanKey		subkey = (ScanKey) DatumGetPointer(skey->sk_argument);
	int32		cmpresult = 0;
	bool		result;

	/* First subkey should be same as the header says */
	Assert(subkey->sk_attno == skey->sk_attno);

	/* Loop over columns of the row condition */
	for (;;)
	{
		Datum		datum;
		bool		isNull;

		Assert(subkey->sk_flags & SK_ROW_MEMBER);

		if (subkey->sk_attno > tupnatts)
		{
			/*
			 * This attribute is truncated (must be high key).  The value for
			 * this attribute in the first non-pivot tuple on the page to the
			 * right could be any possible value.  Assume that truncated
			 * attribute passes the qual.
			 */
			Assert(ScanDirectionIsForward(dir));
			cmpresult = 0;
			if (subkey->sk_flags & SK_ROW_END)
				break;
			subkey++;
			continue;
		}

		datum = index_getattr(tuple,
							  subkey->sk_attno,
							  tupdesc,
							  &isNull);

		if (isNull)
		{
			if (subkey->sk_flags & SK_BT_NULLS_FIRST)
			{
				/*
				 * Since NULLs are sorted before non-NULLs, we know we have
				 * reached the lower limit of the range of values for this
				 * index attr.  On a backward scan, we can stop if this qual
				 * is one of the "must match" subset.  We can stop regardless
				 * of whether the qual is > or <, so long as it's required,
				 * because it's not possible for any future tuples to pass. On
				 * a forward scan, however, we must keep going, because we may
				 * have initially positioned to the start of the index.
				 */
				if ((subkey->sk_flags & (SK_BT_REQFWD | SK_BT_REQBKWD)) &&
					ScanDirectionIsBackward(dir))
					*continuescan = false;
			}
			else
			{
				/*
				 * Since NULLs are sorted after non-NULLs, we know we have
				 * reached the upper limit of the range of values for this
				 * index attr.  On a forward scan, we can stop if this qual is
				 * one of the "must match" subset.  We can stop regardless of
				 * whether the qual is > or <, so long as it's required,
				 * because it's not possible for any future tuples to pass. On
				 * a backward scan, however, we must keep going, because we
				 * may have initially positioned to the end of the index.
				 */
				if ((subkey->sk_flags & (SK_BT_REQFWD | SK_BT_REQBKWD)) &&
					ScanDirectionIsForward(dir))
					*continuescan = false;
			}

			/*
			 * In any case, this indextuple doesn't match the qual.
			 */
			return false;
		}

		if (subkey->sk_flags & SK_ISNULL)
		{
			/*
			 * Unlike the simple-scankey case, this isn't a disallowed case.
			 * But it can never match.  If all the earlier row comparison
			 * columns are required for the scan direction, we can stop the
			 * scan, because there can't be another tuple that will succeed.
			 */
			if (subkey != (ScanKey) DatumGetPointer(skey->sk_argument))
				subkey--;
			if ((subkey->sk_flags & SK_BT_REQFWD) &&
				ScanDirectionIsForward(dir))
				*continuescan = false;
			else if ((subkey->sk_flags & SK_BT_REQBKWD) &&
					 ScanDirectionIsBackward(dir))
				*continuescan = false;
			return false;
		}

		/* Perform the test --- three-way comparison not bool operator */
		cmpresult = DatumGetInt32(FunctionCall2Coll(&subkey->sk_func,
													subkey->sk_collation,
													datum,
													subkey->sk_argument));

		if (subkey->sk_flags & SK_BT_DESC)
			INVERT_COMPARE_RESULT(cmpresult);

		/* Done comparing if unequal, else advance to next column */
		if (cmpresult != 0)
			break;

		if (subkey->sk_flags & SK_ROW_END)
			break;
		subkey++;
	}

	/*
	 * At this point cmpresult indicates the overall result of the row
	 * comparison, and subkey points to the deciding column (or the last
	 * column if the result is "=").
	 */
	switch (subkey->sk_strategy)
	{
			/* EQ and NE cases aren't allowed here */
		case BTLessStrategyNumber:
			result = (cmpresult < 0);
			break;
		case BTLessEqualStrategyNumber:
			result = (cmpresult <= 0);
			break;
		case BTGreaterEqualStrategyNumber:
			result = (cmpresult >= 0);
			break;
		case BTGreaterStrategyNumber:
			result = (cmpresult > 0);
			break;
		default:
			elog(ERROR, "unrecognized RowCompareType: %d",
				 (int) subkey->sk_strategy);
			result = 0;			/* keep compiler quiet */
			break;
	}

	if (!result)
	{
		/*
		 * Tuple fails this qual.  If it's a required qual for the current
		 * scan direction, then we can conclude no further tuples will pass,
		 * either.  Note we have to look at the deciding column, not
		 * necessarily the first or last column of the row condition.
		 */
		if ((subkey->sk_flags & SK_BT_REQFWD) &&
			ScanDirectionIsForward(dir))
			*continuescan = false;
		else if ((subkey->sk_flags & SK_BT_REQBKWD) &&
				 ScanDirectionIsBackward(dir))
			*continuescan = false;
	}

	return result;
}