#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cvec {int nchrs; int chrspace; int nranges; int rangespace; int cclasscode; TYPE_1__* ranges; TYPE_1__* chrs; } ;
typedef  scalar_t__ pg_wchar ;
typedef  scalar_t__ (* pg_wc_probefunc ) (scalar_t__) ;
struct TYPE_7__ {scalar_t__ collation; struct cvec cv; struct TYPE_7__* next; scalar_t__ (* probefunc ) (scalar_t__) ;} ;
typedef  TYPE_1__ pg_ctype_cache ;
typedef  TYPE_1__ chr ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SIMPLE_CHR ; 
#define  PG_REGEX_LOCALE_1BYTE 133 
#define  PG_REGEX_LOCALE_1BYTE_L 132 
#define  PG_REGEX_LOCALE_C 131 
#define  PG_REGEX_LOCALE_ICU 130 
#define  PG_REGEX_LOCALE_WIDE 129 
#define  PG_REGEX_LOCALE_WIDE_L 128 
 int /*<<< orphan*/  UCHAR_MAX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__* pg_ctype_cache_list ; 
 scalar_t__ pg_regex_collation ; 
 int pg_regex_strategy ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  store_match (TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ stub1 (scalar_t__) ; 

__attribute__((used)) static struct cvec *
pg_ctype_get_cache(pg_wc_probefunc probefunc, int cclasscode)
{
	pg_ctype_cache *pcc;
	pg_wchar	max_chr;
	pg_wchar	cur_chr;
	int			nmatches;
	chr		   *newchrs;

	/*
	 * Do we already have the answer cached?
	 */
	for (pcc = pg_ctype_cache_list; pcc != NULL; pcc = pcc->next)
	{
		if (pcc->probefunc == probefunc &&
			pcc->collation == pg_regex_collation)
			return &pcc->cv;
	}

	/*
	 * Nope, so initialize some workspace ...
	 */
	pcc = (pg_ctype_cache *) malloc(sizeof(pg_ctype_cache));
	if (pcc == NULL)
		return NULL;
	pcc->probefunc = probefunc;
	pcc->collation = pg_regex_collation;
	pcc->cv.nchrs = 0;
	pcc->cv.chrspace = 128;
	pcc->cv.chrs = (chr *) malloc(pcc->cv.chrspace * sizeof(chr));
	pcc->cv.nranges = 0;
	pcc->cv.rangespace = 64;
	pcc->cv.ranges = (chr *) malloc(pcc->cv.rangespace * sizeof(chr) * 2);
	if (pcc->cv.chrs == NULL || pcc->cv.ranges == NULL)
		goto out_of_memory;
	pcc->cv.cclasscode = cclasscode;

	/*
	 * Decide how many character codes we ought to look through.  In general
	 * we don't go past MAX_SIMPLE_CHR; chr codes above that are handled at
	 * runtime using the "high colormap" mechanism.  However, in C locale
	 * there's no need to go further than 127, and if we only have a 1-byte
	 * <ctype.h> API there's no need to go further than that can handle.
	 *
	 * If it's not MAX_SIMPLE_CHR that's constraining the search, mark the
	 * output cvec as not having any locale-dependent behavior, since there
	 * will be no need to do any run-time locale checks.  (The #if's here
	 * would always be true for production values of MAX_SIMPLE_CHR, but it's
	 * useful to allow it to be small for testing purposes.)
	 */
	switch (pg_regex_strategy)
	{
		case PG_REGEX_LOCALE_C:
#if MAX_SIMPLE_CHR >= 127
			max_chr = (pg_wchar) 127;
			pcc->cv.cclasscode = -1;
#else
			max_chr = (pg_wchar) MAX_SIMPLE_CHR;
#endif
			break;
		case PG_REGEX_LOCALE_WIDE:
		case PG_REGEX_LOCALE_WIDE_L:
			max_chr = (pg_wchar) MAX_SIMPLE_CHR;
			break;
		case PG_REGEX_LOCALE_1BYTE:
		case PG_REGEX_LOCALE_1BYTE_L:
#if MAX_SIMPLE_CHR >= UCHAR_MAX
			max_chr = (pg_wchar) UCHAR_MAX;
			pcc->cv.cclasscode = -1;
#else
			max_chr = (pg_wchar) MAX_SIMPLE_CHR;
#endif
			break;
		case PG_REGEX_LOCALE_ICU:
			max_chr = (pg_wchar) MAX_SIMPLE_CHR;
			break;
		default:
			max_chr = 0;		/* can't get here, but keep compiler quiet */
			break;
	}

	/*
	 * And scan 'em ...
	 */
	nmatches = 0;				/* number of consecutive matches */

	for (cur_chr = 0; cur_chr <= max_chr; cur_chr++)
	{
		if ((*probefunc) (cur_chr))
			nmatches++;
		else if (nmatches > 0)
		{
			if (!store_match(pcc, cur_chr - nmatches, nmatches))
				goto out_of_memory;
			nmatches = 0;
		}
	}

	if (nmatches > 0)
		if (!store_match(pcc, cur_chr - nmatches, nmatches))
			goto out_of_memory;

	/*
	 * We might have allocated more memory than needed, if so free it
	 */
	if (pcc->cv.nchrs == 0)
	{
		free(pcc->cv.chrs);
		pcc->cv.chrs = NULL;
		pcc->cv.chrspace = 0;
	}
	else if (pcc->cv.nchrs < pcc->cv.chrspace)
	{
		newchrs = (chr *) realloc(pcc->cv.chrs,
								  pcc->cv.nchrs * sizeof(chr));
		if (newchrs == NULL)
			goto out_of_memory;
		pcc->cv.chrs = newchrs;
		pcc->cv.chrspace = pcc->cv.nchrs;
	}
	if (pcc->cv.nranges == 0)
	{
		free(pcc->cv.ranges);
		pcc->cv.ranges = NULL;
		pcc->cv.rangespace = 0;
	}
	else if (pcc->cv.nranges < pcc->cv.rangespace)
	{
		newchrs = (chr *) realloc(pcc->cv.ranges,
								  pcc->cv.nranges * sizeof(chr) * 2);
		if (newchrs == NULL)
			goto out_of_memory;
		pcc->cv.ranges = newchrs;
		pcc->cv.rangespace = pcc->cv.nranges;
	}

	/*
	 * Success, link it into cache chain
	 */
	pcc->next = pg_ctype_cache_list;
	pg_ctype_cache_list = pcc;

	return &pcc->cv;

	/*
	 * Failure, clean up
	 */
out_of_memory:
	if (pcc->cv.chrs)
		free(pcc->cv.chrs);
	if (pcc->cv.ranges)
		free(pcc->cv.ranges);
	free(pcc);

	return NULL;
}