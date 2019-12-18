#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trgm ;
struct TYPE_5__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ TRGM ;

/* Variables and functions */
 int /*<<< orphan*/  ARRKEY ; 
 int CALCGTSIZE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GETARR (TYPE_1__*) ; 
 int LPADDING ; 
 int RPADDING ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int TRGMHDRSIZE ; 
 int /*<<< orphan*/  comp_trgm ; 
 char* get_wildcard_part (char const*,int,char*,int*,int*) ; 
 char* lowerstr_with_len (char*,int) ; 
 int /*<<< orphan*/ * make_trigrams (int /*<<< orphan*/ *,char*,int,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  protect_out_of_mem (int) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int qunique (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

TRGM *
generate_wildcard_trgm(const char *str, int slen)
{
	TRGM	   *trg;
	char	   *buf,
			   *buf2;
	trgm	   *tptr;
	int			len,
				charlen,
				bytelen;
	const char *eword;

	protect_out_of_mem(slen);

	trg = (TRGM *) palloc(TRGMHDRSIZE + sizeof(trgm) * (slen / 2 + 1) * 3);
	trg->flag = ARRKEY;
	SET_VARSIZE(trg, TRGMHDRSIZE);

	if (slen + LPADDING + RPADDING < 3 || slen == 0)
		return trg;

	tptr = GETARR(trg);

	/* Allocate a buffer for blank-padded, but not yet case-folded, words */
	buf = palloc(sizeof(char) * (slen + 4));

	/*
	 * Extract trigrams from each substring extracted by get_wildcard_part.
	 */
	eword = str;
	while ((eword = get_wildcard_part(eword, slen - (eword - str),
									  buf, &bytelen, &charlen)) != NULL)
	{
#ifdef IGNORECASE
		buf2 = lowerstr_with_len(buf, bytelen);
		bytelen = strlen(buf2);
#else
		buf2 = buf;
#endif

		/*
		 * count trigrams
		 */
		tptr = make_trigrams(tptr, buf2, bytelen, charlen);

#ifdef IGNORECASE
		pfree(buf2);
#endif
	}

	pfree(buf);

	if ((len = tptr - GETARR(trg)) == 0)
		return trg;

	/*
	 * Make trigrams unique.
	 */
	if (len > 1)
	{
		qsort((void *) GETARR(trg), len, sizeof(trgm), comp_trgm);
		len = qunique(GETARR(trg), len, sizeof(trgm), comp_trgm);
	}

	SET_VARSIZE(trg, CALCGTSIZE(ARRKEY, len));

	return trg;
}