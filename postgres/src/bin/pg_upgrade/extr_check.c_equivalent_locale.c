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

/* Variables and functions */
 char* get_canonical_locale_name (int,char const*) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 scalar_t__ pg_strcasecmp (char const*,char const*) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static bool
equivalent_locale(int category, const char *loca, const char *locb)
{
	const char *chara;
	const char *charb;
	char	   *canona;
	char	   *canonb;
	int			lena;
	int			lenb;

	/*
	 * If the names are equal, the locales are equivalent. Checking this first
	 * avoids calling setlocale() in the common case that the names are equal.
	 * That's a good thing, if setlocale() is buggy, for example.
	 */
	if (pg_strcasecmp(loca, locb) == 0)
		return true;

	/*
	 * Not identical. Canonicalize both names, remove the encoding parts, and
	 * try again.
	 */
	canona = get_canonical_locale_name(category, loca);
	chara = strrchr(canona, '.');
	lena = chara ? (chara - canona) : strlen(canona);

	canonb = get_canonical_locale_name(category, locb);
	charb = strrchr(canonb, '.');
	lenb = charb ? (charb - canonb) : strlen(canonb);

	if (lena == lenb && pg_strncasecmp(canona, canonb, lena) == 0)
	{
		pg_free(canona);
		pg_free(canonb);
		return true;
	}

	pg_free(canona);
	pg_free(canonb);
	return false;
}