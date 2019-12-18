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
union un_fmt_comb {unsigned int uint_val; unsigned long luint_val; int /*<<< orphan*/ * str_val; } ;

/* Variables and functions */
#define  PGTYPES_TYPE_STRING_MALLOCED 130 
#define  PGTYPES_TYPE_UINT 129 
#define  PGTYPES_TYPE_UINT_LONG 128 
 int /*<<< orphan*/  errno ; 
 char* find_end_token (char*,char*) ; 
 int /*<<< orphan*/ * pgtypes_strdup (char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
pgtypes_defmt_scan(union un_fmt_comb *scan_val, int scan_type, char **pstr, char *pfmt)
{
	/*
	 * scan everything between pstr and pstr_end. This is not including the
	 * last character so we might set it to '\0' for the parsing
	 */

	char		last_char;
	int			err = 0;
	char	   *pstr_end;
	char	   *strtol_end = NULL;

	while (**pstr == ' ')
		pstr++;
	pstr_end = find_end_token(*pstr, pfmt);
	if (!pstr_end)
	{
		/* there was an error, no match */
		return 1;
	}
	last_char = *pstr_end;
	*pstr_end = '\0';

	switch (scan_type)
	{
		case PGTYPES_TYPE_UINT:

			/*
			 * numbers may be blank-padded, this is the only deviation from
			 * the fmt-string we accept
			 */
			while (**pstr == ' ')
				(*pstr)++;
			errno = 0;
			scan_val->uint_val = (unsigned int) strtol(*pstr, &strtol_end, 10);
			if (errno)
				err = 1;
			break;
		case PGTYPES_TYPE_UINT_LONG:
			while (**pstr == ' ')
				(*pstr)++;
			errno = 0;
			scan_val->luint_val = (unsigned long int) strtol(*pstr, &strtol_end, 10);
			if (errno)
				err = 1;
			break;
		case PGTYPES_TYPE_STRING_MALLOCED:
			scan_val->str_val = pgtypes_strdup(*pstr);
			if (scan_val->str_val == NULL)
				err = 1;
			break;
	}
	if (strtol_end && *strtol_end)
		*pstr = strtol_end;
	else
		*pstr = pstr_end;
	*pstr_end = last_char;
	return err;
}