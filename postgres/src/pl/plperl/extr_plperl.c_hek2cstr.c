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
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HE ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  FREETMPS ; 
 int /*<<< orphan*/ * HeSVKEY_force (int /*<<< orphan*/ *) ; 
 scalar_t__ HeUTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SvUTF8_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 char* sv2cstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
hek2cstr(HE *he)
{
	dTHX;
	char	   *ret;
	SV		   *sv;

	/*
	 * HeSVKEY_force will return a temporary mortal SV*, so we need to make
	 * sure to free it with ENTER/SAVE/FREE/LEAVE
	 */
	ENTER;
	SAVETMPS;

	/*-------------------------
	 * Unfortunately,  while HeUTF8 is true for most things > 256, for values
	 * 128..255 it's not, but perl will treat them as unicode code points if
	 * the utf8 flag is not set ( see The "Unicode Bug" in perldoc perlunicode
	 * for more)
	 *
	 * So if we did the expected:
	 *	  if (HeUTF8(he))
	 *		  utf_u2e(key...);
	 *	  else // must be ascii
	 *		  return HePV(he);
	 * we won't match columns with codepoints from 128..255
	 *
	 * For a more concrete example given a column with the name of the unicode
	 * codepoint U+00ae (registered sign) and a UTF8 database and the perl
	 * return_next { "\N{U+00ae}=>'text } would always fail as heUTF8 returns
	 * 0 and HePV() would give us a char * with 1 byte contains the decimal
	 * value 174
	 *
	 * Perl has the brains to know when it should utf8 encode 174 properly, so
	 * here we force it into an SV so that perl will figure it out and do the
	 * right thing
	 *-------------------------
	 */

	sv = HeSVKEY_force(he);
	if (HeUTF8(he))
		SvUTF8_on(sv);
	ret = sv2cstr(sv);

	/* free sv */
	FREETMPS;
	LEAVE;

	return ret;
}