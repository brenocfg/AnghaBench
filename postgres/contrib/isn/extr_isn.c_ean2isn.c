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
typedef  enum isn_type { ____Placeholder_isn_type } isn_type ;
typedef  int /*<<< orphan*/  eanbuf ;
typedef  int ean13 ;

/* Variables and functions */
 int ANY ; 
 int EAN13 ; 
 char* EAN13_FORMAT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int INVALID ; 
 int ISBN ; 
 int ISMN ; 
 int ISSN ; 
 int /*<<< orphan*/  MAXEAN13LEN ; 
 int UINT64CONST (int) ; 
 int UPC ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * isn_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static bool
ean2isn(ean13 ean, bool errorOK, ean13 *result, enum isn_type accept)
{
	enum isn_type type = INVALID;

	char		buf[MAXEAN13LEN + 1];
	char	   *aux;
	unsigned	digval;
	unsigned	search;
	ean13		ret = ean;

	ean >>= 1;
	/* verify it's in the EAN13 range */
	if (ean > UINT64CONST(9999999999999))
		goto eantoobig;

	/* convert the number */
	search = 0;
	aux = buf + 13;
	*aux = '\0';				/* terminate string; aux points to last digit */
	do
	{
		digval = (unsigned) (ean % 10); /* get the decimal value */
		ean /= 10;				/* get next digit */
		*--aux = (char) (digval + '0'); /* convert to ascii and store */
	} while (ean && search++ < 12);
	while (search++ < 12)
		*--aux = '0';			/* fill the remaining EAN13 with '0' */

	/* find out the data type: */
	if (strncmp("978", buf, 3) == 0)
	{							/* ISBN */
		type = ISBN;
	}
	else if (strncmp("977", buf, 3) == 0)
	{							/* ISSN */
		type = ISSN;
	}
	else if (strncmp("9790", buf, 4) == 0)
	{							/* ISMN */
		type = ISMN;
	}
	else if (strncmp("979", buf, 3) == 0)
	{							/* ISBN-13 */
		type = ISBN;
	}
	else if (*buf == '0')
	{							/* UPC */
		type = UPC;
	}
	else
	{
		type = EAN13;
	}
	if (accept != ANY && accept != EAN13 && accept != type)
		goto eanwrongtype;

	*result = ret;
	return true;

eanwrongtype:
	if (!errorOK)
	{
		if (type != EAN13)
		{
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("cannot cast EAN13(%s) to %s for number: \"%s\"",
							isn_names[type], isn_names[accept], buf)));
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("cannot cast %s to %s for number: \"%s\"",
							isn_names[type], isn_names[accept], buf)));
		}
	}
	return false;

eantoobig:
	if (!errorOK)
	{
		char		eanbuf[64];

		/*
		 * Format the number separately to keep the machine-dependent format
		 * code out of the translatable message text
		 */
		snprintf(eanbuf, sizeof(eanbuf), EAN13_FORMAT, ean);
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for %s type",
						eanbuf, isn_names[type])));
	}
	return false;
}