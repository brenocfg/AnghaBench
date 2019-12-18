#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  WordEntryPos ;
struct TYPE_12__ {int pos; int len; scalar_t__ haspos; } ;
typedef  TYPE_1__ WordEntry ;
struct TYPE_13__ {int size; } ;
typedef  TYPE_2__* TSVector ;

/* Variables and functions */
 TYPE_1__* ARRPTR (TYPE_2__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CALCDATASIZE (int,int) ; 
 int POSDATALEN (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int SHORTALIGN (int) ; 
 char* STRPTR (TYPE_2__*) ; 
 int /*<<< orphan*/  VARSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  compare_int ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int qunique (int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TSVector
tsvector_delete_by_indices(TSVector tsv, int *indices_to_delete,
						   int indices_count)
{
	TSVector	tsout;
	WordEntry  *arrin = ARRPTR(tsv),
			   *arrout;
	char	   *data = STRPTR(tsv),
			   *dataout;
	int			i,				/* index in arrin */
				j,				/* index in arrout */
				k,				/* index in indices_to_delete */
				curoff;			/* index in dataout area */

	/*
	 * Sort the filter array to simplify membership checks below.  Also, get
	 * rid of any duplicate entries, so that we can assume that indices_count
	 * is exactly equal to the number of lexemes that will be removed.
	 */
	if (indices_count > 1)
	{
		qsort(indices_to_delete, indices_count, sizeof(int), compare_int);
		indices_count = qunique(indices_to_delete, indices_count, sizeof(int),
								compare_int);
	}

	/*
	 * Here we overestimate tsout size, since we don't know how much space is
	 * used by the deleted lexeme(s).  We will set exact size below.
	 */
	tsout = (TSVector) palloc0(VARSIZE(tsv));

	/* This count must be correct because STRPTR(tsout) relies on it. */
	tsout->size = tsv->size - indices_count;

	/*
	 * Copy tsv to tsout, skipping lexemes listed in indices_to_delete.
	 */
	arrout = ARRPTR(tsout);
	dataout = STRPTR(tsout);
	curoff = 0;
	for (i = j = k = 0; i < tsv->size; i++)
	{
		/*
		 * If current i is present in indices_to_delete, skip this lexeme.
		 * Since indices_to_delete is already sorted, we only need to check
		 * the current (k'th) entry.
		 */
		if (k < indices_count && i == indices_to_delete[k])
		{
			k++;
			continue;
		}

		/* Copy lexeme and its positions and weights */
		memcpy(dataout + curoff, data + arrin[i].pos, arrin[i].len);
		arrout[j].haspos = arrin[i].haspos;
		arrout[j].len = arrin[i].len;
		arrout[j].pos = curoff;
		curoff += arrin[i].len;
		if (arrin[i].haspos)
		{
			int			len = POSDATALEN(tsv, arrin + i) * sizeof(WordEntryPos)
			+ sizeof(uint16);

			curoff = SHORTALIGN(curoff);
			memcpy(dataout + curoff,
				   STRPTR(tsv) + SHORTALIGN(arrin[i].pos + arrin[i].len),
				   len);
			curoff += len;
		}

		j++;
	}

	/*
	 * k should now be exactly equal to indices_count. If it isn't then the
	 * caller provided us with indices outside of [0, tsv->size) range and
	 * estimation of tsout's size is wrong.
	 */
	Assert(k == indices_count);

	SET_VARSIZE(tsout, CALCDATASIZE(tsout->size, curoff));
	return tsout;
}