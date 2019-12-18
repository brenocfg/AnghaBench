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
typedef  double float8 ;

/* Variables and functions */
#define  DTK_CENTURY 149 
#define  DTK_DAY 148 
#define  DTK_DECADE 147 
#define  DTK_DOW 146 
#define  DTK_DOY 145 
#define  DTK_EPOCH 144 
#define  DTK_HOUR 143 
#define  DTK_ISODOW 142 
#define  DTK_ISOYEAR 141 
#define  DTK_JULIAN 140 
#define  DTK_MICROSEC 139 
#define  DTK_MILLENNIUM 138 
#define  DTK_MILLISEC 137 
#define  DTK_MINUTE 136 
#define  DTK_MONTH 135 
#define  DTK_QUARTER 134 
#define  DTK_SECOND 133 
#define  DTK_TZ 132 
#define  DTK_TZ_HOUR 131 
#define  DTK_TZ_MINUTE 130 
#define  DTK_WEEK 129 
#define  DTK_YEAR 128 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int RESERV ; 
 int UNITS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 double get_float8_infinity () ; 

__attribute__((used)) static float8
NonFiniteTimestampTzPart(int type, int unit, char *lowunits,
						 bool isNegative, bool isTz)
{
	if ((type != UNITS) && (type != RESERV))
	{
		if (isTz)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("timestamp with time zone units \"%s\" not recognized",
							lowunits)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("timestamp units \"%s\" not recognized",
							lowunits)));
	}

	switch (unit)
	{
			/* Oscillating units */
		case DTK_MICROSEC:
		case DTK_MILLISEC:
		case DTK_SECOND:
		case DTK_MINUTE:
		case DTK_HOUR:
		case DTK_DAY:
		case DTK_MONTH:
		case DTK_QUARTER:
		case DTK_WEEK:
		case DTK_DOW:
		case DTK_ISODOW:
		case DTK_DOY:
		case DTK_TZ:
		case DTK_TZ_MINUTE:
		case DTK_TZ_HOUR:
			return 0.0;

			/* Monotonically-increasing units */
		case DTK_YEAR:
		case DTK_DECADE:
		case DTK_CENTURY:
		case DTK_MILLENNIUM:
		case DTK_JULIAN:
		case DTK_ISOYEAR:
		case DTK_EPOCH:
			if (isNegative)
				return -get_float8_infinity();
			else
				return get_float8_infinity();

		default:
			if (isTz)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("timestamp with time zone units \"%s\" not supported",
								lowunits)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("timestamp units \"%s\" not supported",
								lowunits)));
			return 0.0;			/* keep compiler quiet */
	}
}