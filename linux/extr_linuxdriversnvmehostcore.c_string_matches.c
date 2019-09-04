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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool string_matches(const char *idstr, const char *match, size_t len)
{
	size_t matchlen;

	if (!match)
		return true;

	matchlen = strlen(match);
	WARN_ON_ONCE(matchlen > len);

	if (memcmp(idstr, match, matchlen))
		return false;

	for (; matchlen < len; matchlen++)
		if (idstr[matchlen] != ' ')
			return false;

	return true;
}