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
typedef  int /*<<< orphan*/  timestamp ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
#define  DTK_DATE 131 
#define  DTK_EARLY 130 
#define  DTK_EPOCH 129 
#define  DTK_LATE 128 
 scalar_t__ DecodeDateTime (char**,int*,int,int*,struct tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAXDATEFIELDS ; 
 int MAXDATELEN ; 
 scalar_t__ PGTYPES_TS_BAD_TIMESTAMP ; 
 scalar_t__ ParseDateTime (char*,char*,char**,int*,int*,char**) ; 
 int /*<<< orphan*/  SetEpochTimestamp () ; 
 int /*<<< orphan*/  TIMESTAMP_NOBEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESTAMP_NOEND (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tm2timestamp (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

timestamp
PGTYPEStimestamp_from_asc(char *str, char **endptr)
{
	timestamp	result;
	int64		noresult = 0;
	fsec_t		fsec;
	struct tm	tt,
			   *tm = &tt;
	int			dtype;
	int			nf;
	char	   *field[MAXDATEFIELDS];
	int			ftype[MAXDATEFIELDS];
	char		lowstr[MAXDATELEN + MAXDATEFIELDS];
	char	   *realptr;
	char	  **ptr = (endptr != NULL) ? endptr : &realptr;

	if (strlen(str) > MAXDATELEN)
	{
		errno = PGTYPES_TS_BAD_TIMESTAMP;
		return noresult;
	}

	if (ParseDateTime(str, lowstr, field, ftype, &nf, ptr) != 0 ||
		DecodeDateTime(field, ftype, nf, &dtype, tm, &fsec, 0) != 0)
	{
		errno = PGTYPES_TS_BAD_TIMESTAMP;
		return noresult;
	}

	switch (dtype)
	{
		case DTK_DATE:
			if (tm2timestamp(tm, fsec, NULL, &result) != 0)
			{
				errno = PGTYPES_TS_BAD_TIMESTAMP;
				return noresult;
			}
			break;

		case DTK_EPOCH:
			result = SetEpochTimestamp();
			break;

		case DTK_LATE:
			TIMESTAMP_NOEND(result);
			break;

		case DTK_EARLY:
			TIMESTAMP_NOBEGIN(result);
			break;

		default:
			errno = PGTYPES_TS_BAD_TIMESTAMP;
			return noresult;
	}

	/* AdjustTimestampForTypmod(&result, typmod); */

	/*
	 * Since it's difficult to test for noresult, make sure errno is 0 if no
	 * error occurred.
	 */
	errno = 0;
	return result;
}