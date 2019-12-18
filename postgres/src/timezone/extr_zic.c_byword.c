#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lookup {char const* l_word; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ciequal (char const*,char const*) ; 
 scalar_t__ ciprefix (char const*,char const*) ; 
 scalar_t__ itsabbr (char const*,char const*) ; 
 struct lookup const* lasts ; 
 scalar_t__ noise ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,...) ; 
 struct lookup* wday_names ; 

__attribute__((used)) static const struct lookup *
byword(const char *word, const struct lookup *table)
{
	const struct lookup *foundlp;
	const struct lookup *lp;

	if (word == NULL || table == NULL)
		return NULL;

	/*
	 * If TABLE is LASTS and the word starts with "last" followed by a
	 * non-'-', skip the "last" and look in WDAY_NAMES instead. Warn about any
	 * usage of the undocumented prefix "last-".
	 */
	if (table == lasts && ciprefix("last", word) && word[4])
	{
		if (word[4] == '-')
			warning(_("\"%s\" is undocumented; use \"last%s\" instead"),
					word, word + 5);
		else
		{
			word += 4;
			table = wday_names;
		}
	}

	/*
	 * Look for exact match.
	 */
	for (lp = table; lp->l_word != NULL; ++lp)
		if (ciequal(word, lp->l_word))
			return lp;

	/*
	 * Look for inexact match.
	 */
	foundlp = NULL;
	for (lp = table; lp->l_word != NULL; ++lp)
		if (ciprefix(word, lp->l_word))
		{
			if (foundlp == NULL)
				foundlp = lp;
			else
				return NULL;	/* multiple inexact matches */
		}

	if (foundlp && noise)
	{
		/* Warn about any backward-compatibility issue with pre-2017c zic.  */
		bool		pre_2017c_match = false;

		for (lp = table; lp->l_word; lp++)
			if (itsabbr(word, lp->l_word))
			{
				if (pre_2017c_match)
				{
					warning(_("\"%s\" is ambiguous in pre-2017c zic"), word);
					break;
				}
				pre_2017c_match = true;
			}
	}

	return foundlp;
}