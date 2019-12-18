#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t max_kw_len; int (* hash ) (char const*,size_t) ;int num_keywords; } ;
typedef  TYPE_1__ ScanKeywordList ;

/* Variables and functions */
 char* GetScanKeyword (int,TYPE_1__ const*) ; 
 size_t strlen (char const*) ; 
 int stub1 (char const*,size_t) ; 

int
ScanKeywordLookup(const char *str,
				  const ScanKeywordList *keywords)
{
	size_t		len;
	int			h;
	const char *kw;

	/*
	 * Reject immediately if too long to be any keyword.  This saves useless
	 * hashing and downcasing work on long strings.
	 */
	len = strlen(str);
	if (len > keywords->max_kw_len)
		return -1;

	/*
	 * Compute the hash function.  We assume it was generated to produce
	 * case-insensitive results.  Since it's a perfect hash, we need only
	 * match to the specific keyword it identifies.
	 */
	h = keywords->hash(str, len);

	/* An out-of-range result implies no match */
	if (h < 0 || h >= keywords->num_keywords)
		return -1;

	/*
	 * Compare character-by-character to see if we have a match, applying an
	 * ASCII-only downcasing to the input characters.  We must not use
	 * tolower() since it may produce the wrong translation in some locales
	 * (eg, Turkish).
	 */
	kw = GetScanKeyword(h, keywords);
	while (*str != '\0')
	{
		char		ch = *str++;

		if (ch >= 'A' && ch <= 'Z')
			ch += 'a' - 'A';
		if (ch != *kw++)
			return -1;
	}
	if (*kw != '\0')
		return -1;

	/* Success! */
	return h;
}