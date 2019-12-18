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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint32 ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ typid; int buflen1; char* buf1; int last_len1; int cache_blob; char* buf2; int last_len2; int buflen2; int /*<<< orphan*/  abbr_card; int /*<<< orphan*/  full_card; TYPE_3__* locale; scalar_t__ collate_c; } ;
typedef  TYPE_4__ VarStringSortSupport ;
typedef  char VarString ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UCharIterator ;
typedef  char UChar ;
struct TYPE_11__ {scalar_t__ ssup_extra; } ;
struct TYPE_7__ {int /*<<< orphan*/  ucol; } ;
struct TYPE_8__ {int /*<<< orphan*/  lt; TYPE_1__ icu; } ;
struct TYPE_9__ {scalar_t__ provider; TYPE_2__ info; } ;
typedef  TYPE_5__* SortSupport ;
typedef  int Size ;
typedef  int Datum ;

/* Variables and functions */
 scalar_t__ BPCHAROID ; 
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ COLLPROVIDER_LIBC ; 
 int DatumBigEndianToNative (int) ; 
 int DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 char* DatumGetVarStringPP (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 void* Max (int,int) ; 
 int MaxAllocSize ; 
 int Min (int,int) ; 
 int PG_CACHE_LINE_SIZE ; 
 scalar_t__ PG_UTF8 ; 
 int PointerGetDatum (char*) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 char* VARDATA_ANY (char*) ; 
 int VARSIZE_ANY_EXHDR (char*) ; 
 int /*<<< orphan*/  addHyperLogLog (int /*<<< orphan*/ *,int) ; 
 int bpchartruelen (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_any (unsigned char*,int) ; 
 int /*<<< orphan*/  hash_uint32 (int) ; 
 int icu_to_uchar (char**,char*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 void* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int strxfrm (char*,char*,int) ; 
 int strxfrm_l (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_errorName (int /*<<< orphan*/ ) ; 
 int ucol_getSortKey (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int ucol_nextSortKeyPart (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiter_setUTF8 (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static Datum
varstr_abbrev_convert(Datum original, SortSupport ssup)
{
	VarStringSortSupport *sss = (VarStringSortSupport *) ssup->ssup_extra;
	VarString  *authoritative = DatumGetVarStringPP(original);
	char	   *authoritative_data = VARDATA_ANY(authoritative);

	/* working state */
	Datum		res;
	char	   *pres;
	int			len;
	uint32		hash;

	pres = (char *) &res;
	/* memset(), so any non-overwritten bytes are NUL */
	memset(pres, 0, sizeof(Datum));
	len = VARSIZE_ANY_EXHDR(authoritative);

	/* Get number of bytes, ignoring trailing spaces */
	if (sss->typid == BPCHAROID)
		len = bpchartruelen(authoritative_data, len);

	/*
	 * If we're using the C collation, use memcpy(), rather than strxfrm(), to
	 * abbreviate keys.  The full comparator for the C locale is always
	 * memcmp().  It would be incorrect to allow bytea callers (callers that
	 * always force the C collation -- bytea isn't a collatable type, but this
	 * approach is convenient) to use strxfrm().  This is because bytea
	 * strings may contain NUL bytes.  Besides, this should be faster, too.
	 *
	 * More generally, it's okay that bytea callers can have NUL bytes in
	 * strings because varstrcmp_abbrev() need not make a distinction between
	 * terminating NUL bytes, and NUL bytes representing actual NULs in the
	 * authoritative representation.  Hopefully a comparison at or past one
	 * abbreviated key's terminating NUL byte will resolve the comparison
	 * without consulting the authoritative representation; specifically, some
	 * later non-NUL byte in the longer string can resolve the comparison
	 * against a subsequent terminating NUL in the shorter string.  There will
	 * usually be what is effectively a "length-wise" resolution there and
	 * then.
	 *
	 * If that doesn't work out -- if all bytes in the longer string
	 * positioned at or past the offset of the smaller string's (first)
	 * terminating NUL are actually representative of NUL bytes in the
	 * authoritative binary string (perhaps with some *terminating* NUL bytes
	 * towards the end of the longer string iff it happens to still be small)
	 * -- then an authoritative tie-breaker will happen, and do the right
	 * thing: explicitly consider string length.
	 */
	if (sss->collate_c)
		memcpy(pres, authoritative_data, Min(len, sizeof(Datum)));
	else
	{
		Size		bsize;
#ifdef USE_ICU
		int32_t		ulen = -1;
		UChar	   *uchar = NULL;
#endif

		/*
		 * We're not using the C collation, so fall back on strxfrm or ICU
		 * analogs.
		 */

		/* By convention, we use buffer 1 to store and NUL-terminate */
		if (len >= sss->buflen1)
		{
			pfree(sss->buf1);
			sss->buflen1 = Max(len + 1, Min(sss->buflen1 * 2, MaxAllocSize));
			sss->buf1 = palloc(sss->buflen1);
		}

		/* Might be able to reuse strxfrm() blob from last call */
		if (sss->last_len1 == len && sss->cache_blob &&
			memcmp(sss->buf1, authoritative_data, len) == 0)
		{
			memcpy(pres, sss->buf2, Min(sizeof(Datum), sss->last_len2));
			/* No change affecting cardinality, so no hashing required */
			goto done;
		}

		memcpy(sss->buf1, authoritative_data, len);

		/*
		 * Just like strcoll(), strxfrm() expects a NUL-terminated string. Not
		 * necessary for ICU, but doesn't hurt.
		 */
		sss->buf1[len] = '\0';
		sss->last_len1 = len;

#ifdef USE_ICU
		/* When using ICU and not UTF8, convert string to UChar. */
		if (sss->locale && sss->locale->provider == COLLPROVIDER_ICU &&
			GetDatabaseEncoding() != PG_UTF8)
			ulen = icu_to_uchar(&uchar, sss->buf1, len);
#endif

		/*
		 * Loop: Call strxfrm() or ucol_getSortKey(), possibly enlarge buffer,
		 * and try again.  Both of these functions have the result buffer
		 * content undefined if the result did not fit, so we need to retry
		 * until everything fits, even though we only need the first few bytes
		 * in the end.  When using ucol_nextSortKeyPart(), however, we only
		 * ask for as many bytes as we actually need.
		 */
		for (;;)
		{
#ifdef USE_ICU
			if (sss->locale && sss->locale->provider == COLLPROVIDER_ICU)
			{
				/*
				 * When using UTF8, use the iteration interface so we only
				 * need to produce as many bytes as we actually need.
				 */
				if (GetDatabaseEncoding() == PG_UTF8)
				{
					UCharIterator iter;
					uint32_t	state[2];
					UErrorCode	status;

					uiter_setUTF8(&iter, sss->buf1, len);
					state[0] = state[1] = 0;	/* won't need that again */
					status = U_ZERO_ERROR;
					bsize = ucol_nextSortKeyPart(sss->locale->info.icu.ucol,
												 &iter,
												 state,
												 (uint8_t *) sss->buf2,
												 Min(sizeof(Datum), sss->buflen2),
												 &status);
					if (U_FAILURE(status))
						ereport(ERROR,
								(errmsg("sort key generation failed: %s",
										u_errorName(status))));
				}
				else
					bsize = ucol_getSortKey(sss->locale->info.icu.ucol,
											uchar, ulen,
											(uint8_t *) sss->buf2, sss->buflen2);
			}
			else
#endif
#ifdef HAVE_LOCALE_T
			if (sss->locale && sss->locale->provider == COLLPROVIDER_LIBC)
				bsize = strxfrm_l(sss->buf2, sss->buf1,
								  sss->buflen2, sss->locale->info.lt);
			else
#endif
				bsize = strxfrm(sss->buf2, sss->buf1, sss->buflen2);

			sss->last_len2 = bsize;
			if (bsize < sss->buflen2)
				break;

			/*
			 * Grow buffer and retry.
			 */
			pfree(sss->buf2);
			sss->buflen2 = Max(bsize + 1,
							   Min(sss->buflen2 * 2, MaxAllocSize));
			sss->buf2 = palloc(sss->buflen2);
		}

		/*
		 * Every Datum byte is always compared.  This is safe because the
		 * strxfrm() blob is itself NUL terminated, leaving no danger of
		 * misinterpreting any NUL bytes not intended to be interpreted as
		 * logically representing termination.
		 *
		 * (Actually, even if there were NUL bytes in the blob it would be
		 * okay.  See remarks on bytea case above.)
		 */
		memcpy(pres, sss->buf2, Min(sizeof(Datum), bsize));

#ifdef USE_ICU
		if (uchar)
			pfree(uchar);
#endif
	}

	/*
	 * Maintain approximate cardinality of both abbreviated keys and original,
	 * authoritative keys using HyperLogLog.  Used as cheap insurance against
	 * the worst case, where we do many string transformations for no saving
	 * in full strcoll()-based comparisons.  These statistics are used by
	 * varstr_abbrev_abort().
	 *
	 * First, Hash key proper, or a significant fraction of it.  Mix in length
	 * in order to compensate for cases where differences are past
	 * PG_CACHE_LINE_SIZE bytes, so as to limit the overhead of hashing.
	 */
	hash = DatumGetUInt32(hash_any((unsigned char *) authoritative_data,
								   Min(len, PG_CACHE_LINE_SIZE)));

	if (len > PG_CACHE_LINE_SIZE)
		hash ^= DatumGetUInt32(hash_uint32((uint32) len));

	addHyperLogLog(&sss->full_card, hash);

	/* Hash abbreviated key */
#if SIZEOF_DATUM == 8
	{
		uint32		lohalf,
					hihalf;

		lohalf = (uint32) res;
		hihalf = (uint32) (res >> 32);
		hash = DatumGetUInt32(hash_uint32(lohalf ^ hihalf));
	}
#else							/* SIZEOF_DATUM != 8 */
	hash = DatumGetUInt32(hash_uint32((uint32) res));
#endif

	addHyperLogLog(&sss->abbr_card, hash);

	/* Cache result, perhaps saving an expensive strxfrm() call next time */
	sss->cache_blob = true;
done:

	/*
	 * Byteswap on little-endian machines.
	 *
	 * This is needed so that varstrcmp_abbrev() (an unsigned integer 3-way
	 * comparator) works correctly on all platforms.  If we didn't do this,
	 * the comparator would have to call memcmp() with a pair of pointers to
	 * the first byte of each abbreviated key, which is slower.
	 */
	res = DatumBigEndianToNative(res);

	/* Don't leak memory here */
	if (PointerGetDatum(authoritative) != original)
		pfree(authoritative);

	return res;
}