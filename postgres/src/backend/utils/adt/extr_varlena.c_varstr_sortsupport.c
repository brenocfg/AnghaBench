#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pg_locale_t ;
struct TYPE_7__ {int buflen1; int buflen2; int last_len1; int last_len2; int cache_blob; int collate_c; double prop_card; int /*<<< orphan*/  full_card; int /*<<< orphan*/  abbr_card; scalar_t__ typid; TYPE_1__* locale; scalar_t__ last_returned; void* buf2; void* buf1; } ;
typedef  TYPE_2__ VarStringSortSupport ;
struct TYPE_8__ {int abbreviate; int /*<<< orphan*/  abbrev_abort; int /*<<< orphan*/  abbrev_converter; int /*<<< orphan*/  comparator; int /*<<< orphan*/  abbrev_full_comparator; TYPE_2__* ssup_extra; } ;
struct TYPE_6__ {scalar_t__ provider; } ;
typedef  TYPE_3__* SortSupport ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ BPCHAROID ; 
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ NAMEOID ; 
 scalar_t__ PG_UTF8 ; 
 int TEXTBUFLEN ; 
 int /*<<< orphan*/  bpcharfastcmp_c ; 
 int /*<<< orphan*/  check_collation_set (scalar_t__) ; 
 int /*<<< orphan*/  initHyperLogLog (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lc_collate_is_c (scalar_t__) ; 
 int /*<<< orphan*/  namefastcmp_c ; 
 int /*<<< orphan*/  namefastcmp_locale ; 
 void* palloc (int) ; 
 TYPE_1__* pg_newlocale_from_collation (scalar_t__) ; 
 int /*<<< orphan*/  varlenafastcmp_locale ; 
 int /*<<< orphan*/  varstr_abbrev_abort ; 
 int /*<<< orphan*/  varstr_abbrev_convert ; 
 int /*<<< orphan*/  varstrcmp_abbrev ; 
 int /*<<< orphan*/  varstrfastcmp_c ; 

void
varstr_sortsupport(SortSupport ssup, Oid typid, Oid collid)
{
	bool		abbreviate = ssup->abbreviate;
	bool		collate_c = false;
	VarStringSortSupport *sss;
	pg_locale_t locale = 0;

	check_collation_set(collid);

	/*
	 * If possible, set ssup->comparator to a function which can be used to
	 * directly compare two datums.  If we can do this, we'll avoid the
	 * overhead of a trip through the fmgr layer for every comparison, which
	 * can be substantial.
	 *
	 * Most typically, we'll set the comparator to varlenafastcmp_locale,
	 * which uses strcoll() to perform comparisons.  We use that for the
	 * BpChar case too, but type NAME uses namefastcmp_locale. However, if
	 * LC_COLLATE = C, we can make things quite a bit faster with
	 * varstrfastcmp_c, bpcharfastcmp_c, or namefastcmp_c, all of which use
	 * memcmp() rather than strcoll().
	 */
	if (lc_collate_is_c(collid))
	{
		if (typid == BPCHAROID)
			ssup->comparator = bpcharfastcmp_c;
		else if (typid == NAMEOID)
		{
			ssup->comparator = namefastcmp_c;
			/* Not supporting abbreviation with type NAME, for now */
			abbreviate = false;
		}
		else
			ssup->comparator = varstrfastcmp_c;

		collate_c = true;
	}
	else
	{
		/*
		 * We need a collation-sensitive comparison.  To make things faster,
		 * we'll figure out the collation based on the locale id and cache the
		 * result.
		 */
		if (collid != DEFAULT_COLLATION_OID)
			locale = pg_newlocale_from_collation(collid);

		/*
		 * There is a further exception on Windows.  When the database
		 * encoding is UTF-8 and we are not using the C collation, complex
		 * hacks are required.  We don't currently have a comparator that
		 * handles that case, so we fall back on the slow method of having the
		 * sort code invoke bttextcmp() (in the case of text) via the fmgr
		 * trampoline.  ICU locales work just the same on Windows, however.
		 */
#ifdef WIN32
		if (GetDatabaseEncoding() == PG_UTF8 &&
			!(locale && locale->provider == COLLPROVIDER_ICU))
			return;
#endif

		/*
		 * We use varlenafastcmp_locale except for type NAME.
		 */
		if (typid == NAMEOID)
		{
			ssup->comparator = namefastcmp_locale;
			/* Not supporting abbreviation with type NAME, for now */
			abbreviate = false;
		}
		else
			ssup->comparator = varlenafastcmp_locale;
	}

	/*
	 * Unfortunately, it seems that abbreviation for non-C collations is
	 * broken on many common platforms; testing of multiple versions of glibc
	 * reveals that, for many locales, strcoll() and strxfrm() do not return
	 * consistent results, which is fatal to this optimization.  While no
	 * other libc other than Cygwin has so far been shown to have a problem,
	 * we take the conservative course of action for right now and disable
	 * this categorically.  (Users who are certain this isn't a problem on
	 * their system can define TRUST_STRXFRM.)
	 *
	 * Even apart from the risk of broken locales, it's possible that there
	 * are platforms where the use of abbreviated keys should be disabled at
	 * compile time.  Having only 4 byte datums could make worst-case
	 * performance drastically more likely, for example.  Moreover, macOS's
	 * strxfrm() implementation is known to not effectively concentrate a
	 * significant amount of entropy from the original string in earlier
	 * transformed blobs.  It's possible that other supported platforms are
	 * similarly encumbered.  So, if we ever get past disabling this
	 * categorically, we may still want or need to disable it for particular
	 * platforms.
	 */
#ifndef TRUST_STRXFRM
	if (!collate_c && !(locale && locale->provider == COLLPROVIDER_ICU))
		abbreviate = false;
#endif

	/*
	 * If we're using abbreviated keys, or if we're using a locale-aware
	 * comparison, we need to initialize a VarStringSortSupport object. Both
	 * cases will make use of the temporary buffers we initialize here for
	 * scratch space (and to detect requirement for BpChar semantics from
	 * caller), and the abbreviation case requires additional state.
	 */
	if (abbreviate || !collate_c)
	{
		sss = palloc(sizeof(VarStringSortSupport));
		sss->buf1 = palloc(TEXTBUFLEN);
		sss->buflen1 = TEXTBUFLEN;
		sss->buf2 = palloc(TEXTBUFLEN);
		sss->buflen2 = TEXTBUFLEN;
		/* Start with invalid values */
		sss->last_len1 = -1;
		sss->last_len2 = -1;
		/* Initialize */
		sss->last_returned = 0;
		sss->locale = locale;

		/*
		 * To avoid somehow confusing a strxfrm() blob and an original string,
		 * constantly keep track of the variety of data that buf1 and buf2
		 * currently contain.
		 *
		 * Comparisons may be interleaved with conversion calls.  Frequently,
		 * conversions and comparisons are batched into two distinct phases,
		 * but the correctness of caching cannot hinge upon this.  For
		 * comparison caching, buffer state is only trusted if cache_blob is
		 * found set to false, whereas strxfrm() caching only trusts the state
		 * when cache_blob is found set to true.
		 *
		 * Arbitrarily initialize cache_blob to true.
		 */
		sss->cache_blob = true;
		sss->collate_c = collate_c;
		sss->typid = typid;
		ssup->ssup_extra = sss;

		/*
		 * If possible, plan to use the abbreviated keys optimization.  The
		 * core code may switch back to authoritative comparator should
		 * abbreviation be aborted.
		 */
		if (abbreviate)
		{
			sss->prop_card = 0.20;
			initHyperLogLog(&sss->abbr_card, 10);
			initHyperLogLog(&sss->full_card, 10);
			ssup->abbrev_full_comparator = ssup->comparator;
			ssup->comparator = varstrcmp_abbrev;
			ssup->abbrev_converter = varstr_abbrev_convert;
			ssup->abbrev_abort = varstr_abbrev_abort;
		}
	}
}