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
typedef  scalar_t__ zic_t ;
struct zone {char* z_format; char z_format_specifier; scalar_t__ z_stdoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERCENT_Z_LEN_BOUND ; 
 char* abbroffset (char*,scalar_t__) ; 
 scalar_t__ is_alpha (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static size_t
doabbr(char *abbr, struct zone const *zp, char const *letters,
	   bool isdst, zic_t save, bool doquotes)
{
	char	   *cp;
	char	   *slashp;
	size_t		len;
	char const *format = zp->z_format;

	slashp = strchr(format, '/');
	if (slashp == NULL)
	{
		char		letterbuf[PERCENT_Z_LEN_BOUND + 1];

		if (zp->z_format_specifier == 'z')
			letters = abbroffset(letterbuf, zp->z_stdoff + save);
		else if (!letters)
			letters = "%s";
		sprintf(abbr, format, letters);
	}
	else if (isdst)
	{
		strcpy(abbr, slashp + 1);
	}
	else
	{
		memcpy(abbr, format, slashp - format);
		abbr[slashp - format] = '\0';
	}
	len = strlen(abbr);
	if (!doquotes)
		return len;
	for (cp = abbr; is_alpha(*cp); cp++)
		continue;
	if (len > 0 && *cp == '\0')
		return len;
	abbr[len + 2] = '\0';
	abbr[len + 1] = '>';
	memmove(abbr + 1, abbr, len);
	abbr[0] = '<';
	return len + 2;
}