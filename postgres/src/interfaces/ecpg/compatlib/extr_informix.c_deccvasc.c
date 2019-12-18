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
typedef  int /*<<< orphan*/  numeric ;
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int /*<<< orphan*/  CDECIMALTYPE ; 
 int /*<<< orphan*/  CSTRINGTYPE ; 
 int ECPG_INFORMIX_BAD_EXPONENT ; 
 int ECPG_INFORMIX_BAD_NUMERIC ; 
 int ECPG_INFORMIX_NUM_OVERFLOW ; 
 int ECPG_INFORMIX_NUM_UNDERFLOW ; 
#define  PGTYPES_NUM_BAD_NUMERIC 129 
#define  PGTYPES_NUM_OVERFLOW 128 
 int /*<<< orphan*/  PGTYPESnumeric_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESnumeric_from_asc (char*,int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_to_decimal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ecpg_strndup (char const*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ risnull (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rsetnull (int /*<<< orphan*/ ,char*) ; 

int
deccvasc(const char *cp, int len, decimal *np)
{
	char	   *str;
	int			ret = 0;
	numeric    *result;

	rsetnull(CDECIMALTYPE, (char *) np);
	if (risnull(CSTRINGTYPE, cp))
		return 0;

	str = ecpg_strndup(cp, len);	/* decimal_in always converts the complete
									 * string */
	if (!str)
		ret = ECPG_INFORMIX_NUM_UNDERFLOW;
	else
	{
		errno = 0;
		result = PGTYPESnumeric_from_asc(str, NULL);
		if (!result)
		{
			switch (errno)
			{
				case PGTYPES_NUM_OVERFLOW:
					ret = ECPG_INFORMIX_NUM_OVERFLOW;
					break;
				case PGTYPES_NUM_BAD_NUMERIC:
					ret = ECPG_INFORMIX_BAD_NUMERIC;
					break;
				default:
					ret = ECPG_INFORMIX_BAD_EXPONENT;
					break;
			}
		}
		else
		{
			int			i = PGTYPESnumeric_to_decimal(result, np);

			PGTYPESnumeric_free(result);
			if (i != 0)
				ret = ECPG_INFORMIX_NUM_OVERFLOW;
		}
	}

	free(str);
	return ret;
}