#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {scalar_t__ typid; int buflen1; char* buf1; int buflen2; char* buf2; int last_len1; int last_len2; int cache_blob; int last_returned; TYPE_3__* locale; } ;
typedef  TYPE_4__ VarStringSortSupport ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  char UChar ;
struct TYPE_11__ {int /*<<< orphan*/  ssup_cxt; scalar_t__ ssup_extra; } ;
struct TYPE_7__ {int /*<<< orphan*/  ucol; } ;
struct TYPE_8__ {int /*<<< orphan*/  lt; TYPE_1__ icu; } ;
struct TYPE_9__ {scalar_t__ provider; scalar_t__ deterministic; TYPE_2__ info; } ;
typedef  TYPE_5__* SortSupport ;

/* Variables and functions */
 scalar_t__ BPCHAROID ; 
 scalar_t__ COLLPROVIDER_ICU ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 void* Max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxAllocSize ; 
 void* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ PG_UTF8 ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int bpchartruelen (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu_to_uchar (char**,char*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int strcmp (char*,char*) ; 
 int strcoll (char*,char*) ; 
 int strcoll_l (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_errorName (int /*<<< orphan*/ ) ; 
 int ucol_strcoll (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ucol_strcollUTF8 (int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
varstrfastcmp_locale(char *a1p, int len1, char *a2p, int len2, SortSupport ssup)
{
	VarStringSortSupport *sss = (VarStringSortSupport *) ssup->ssup_extra;
	int			result;
	bool		arg1_match;

	/* Fast pre-check for equality, as discussed in varstr_cmp() */
	if (len1 == len2 && memcmp(a1p, a2p, len1) == 0)
	{
		/*
		 * No change in buf1 or buf2 contents, so avoid changing last_len1 or
		 * last_len2.  Existing contents of buffers might still be used by
		 * next call.
		 *
		 * It's fine to allow the comparison of BpChar padding bytes here,
		 * even though that implies that the memcmp() will usually be
		 * performed for BpChar callers (though multibyte characters could
		 * still prevent that from occurring).  The memcmp() is still very
		 * cheap, and BpChar's funny semantics have us remove trailing spaces
		 * (not limited to padding), so we need make no distinction between
		 * padding space characters and "real" space characters.
		 */
		return 0;
	}

	if (sss->typid == BPCHAROID)
	{
		/* Get true number of bytes, ignoring trailing spaces */
		len1 = bpchartruelen(a1p, len1);
		len2 = bpchartruelen(a2p, len2);
	}

	if (len1 >= sss->buflen1)
	{
		pfree(sss->buf1);
		sss->buflen1 = Max(len1 + 1, Min(sss->buflen1 * 2, MaxAllocSize));
		sss->buf1 = MemoryContextAlloc(ssup->ssup_cxt, sss->buflen1);
	}
	if (len2 >= sss->buflen2)
	{
		pfree(sss->buf2);
		sss->buflen2 = Max(len2 + 1, Min(sss->buflen2 * 2, MaxAllocSize));
		sss->buf2 = MemoryContextAlloc(ssup->ssup_cxt, sss->buflen2);
	}

	/*
	 * We're likely to be asked to compare the same strings repeatedly, and
	 * memcmp() is so much cheaper than strcoll() that it pays to try to cache
	 * comparisons, even though in general there is no reason to think that
	 * that will work out (every string datum may be unique).  Caching does
	 * not slow things down measurably when it doesn't work out, and can speed
	 * things up by rather a lot when it does.  In part, this is because the
	 * memcmp() compares data from cachelines that are needed in L1 cache even
	 * when the last comparison's result cannot be reused.
	 */
	arg1_match = true;
	if (len1 != sss->last_len1 || memcmp(sss->buf1, a1p, len1) != 0)
	{
		arg1_match = false;
		memcpy(sss->buf1, a1p, len1);
		sss->buf1[len1] = '\0';
		sss->last_len1 = len1;
	}

	/*
	 * If we're comparing the same two strings as last time, we can return the
	 * same answer without calling strcoll() again.  This is more likely than
	 * it seems (at least with moderate to low cardinality sets), because
	 * quicksort compares the same pivot against many values.
	 */
	if (len2 != sss->last_len2 || memcmp(sss->buf2, a2p, len2) != 0)
	{
		memcpy(sss->buf2, a2p, len2);
		sss->buf2[len2] = '\0';
		sss->last_len2 = len2;
	}
	else if (arg1_match && !sss->cache_blob)
	{
		/* Use result cached following last actual strcoll() call */
		return sss->last_returned;
	}

	if (sss->locale)
	{
		if (sss->locale->provider == COLLPROVIDER_ICU)
		{
#ifdef USE_ICU
#ifdef HAVE_UCOL_STRCOLLUTF8
			if (GetDatabaseEncoding() == PG_UTF8)
			{
				UErrorCode	status;

				status = U_ZERO_ERROR;
				result = ucol_strcollUTF8(sss->locale->info.icu.ucol,
										  a1p, len1,
										  a2p, len2,
										  &status);
				if (U_FAILURE(status))
					ereport(ERROR,
							(errmsg("collation failed: %s", u_errorName(status))));
			}
			else
#endif
			{
				int32_t		ulen1,
							ulen2;
				UChar	   *uchar1,
						   *uchar2;

				ulen1 = icu_to_uchar(&uchar1, a1p, len1);
				ulen2 = icu_to_uchar(&uchar2, a2p, len2);

				result = ucol_strcoll(sss->locale->info.icu.ucol,
									  uchar1, ulen1,
									  uchar2, ulen2);

				pfree(uchar1);
				pfree(uchar2);
			}
#else							/* not USE_ICU */
			/* shouldn't happen */
			elog(ERROR, "unsupported collprovider: %c", sss->locale->provider);
#endif							/* not USE_ICU */
		}
		else
		{
#ifdef HAVE_LOCALE_T
			result = strcoll_l(sss->buf1, sss->buf2, sss->locale->info.lt);
#else
			/* shouldn't happen */
			elog(ERROR, "unsupported collprovider: %c", sss->locale->provider);
#endif
		}
	}
	else
		result = strcoll(sss->buf1, sss->buf2);

	/* Break tie if necessary. */
	if (result == 0 &&
		(!sss->locale || sss->locale->deterministic))
		result = strcmp(sss->buf1, sss->buf2);

	/* Cache result, perhaps saving an expensive strcoll() call next time */
	sss->cache_blob = false;
	sss->last_returned = result;
	return result;
}