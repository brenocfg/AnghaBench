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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int ECPG_INFORMIX_BAD_DAY ; 
 int ECPG_INFORMIX_BAD_MONTH ; 
 int ECPG_INFORMIX_BAD_YEAR ; 
 int ECPG_INFORMIX_ENOSHORTDATE ; 
 int ECPG_INFORMIX_ENOTDMY ; 
#define  PGTYPES_DATE_BAD_DAY 132 
#define  PGTYPES_DATE_BAD_MONTH 131 
#define  PGTYPES_DATE_ERR_EARGS 130 
#define  PGTYPES_DATE_ERR_ENOSHORTDATE 129 
#define  PGTYPES_DATE_ERR_ENOTDMY 128 
 scalar_t__ PGTYPESdate_defmt_asc (int /*<<< orphan*/ *,char const*,char const*) ; 
 int errno ; 

int
rdefmtdate(date * d, const char *fmt, const char *str)
{
	/* TODO: take care of DBCENTURY environment variable */
	/* PGSQL functions allow all centuries */

	errno = 0;
	if (PGTYPESdate_defmt_asc(d, fmt, str) == 0)
		return 0;

	switch (errno)
	{
		case PGTYPES_DATE_ERR_ENOSHORTDATE:
			return ECPG_INFORMIX_ENOSHORTDATE;
		case PGTYPES_DATE_ERR_EARGS:
		case PGTYPES_DATE_ERR_ENOTDMY:
			return ECPG_INFORMIX_ENOTDMY;
		case PGTYPES_DATE_BAD_DAY:
			return ECPG_INFORMIX_BAD_DAY;
		case PGTYPES_DATE_BAD_MONTH:
			return ECPG_INFORMIX_BAD_MONTH;
		default:
			return ECPG_INFORMIX_BAD_YEAR;
	}
}