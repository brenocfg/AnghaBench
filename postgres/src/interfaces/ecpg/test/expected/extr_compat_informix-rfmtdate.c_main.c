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
 int /*<<< orphan*/  ECPGdebug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_test_defmt (char*,char*) ; 
 int /*<<< orphan*/  date_test_fmt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  date_test_strdate (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rdatestr (int /*<<< orphan*/ ,char*) ; 
 int rmdyjul (short*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main(void)
{
	short mdy[3] = { 11, 23, 1959 };
	char dbuf[11];
	date d;
	int r;

	ECPGdebug(1, stderr);

	r = rmdyjul(mdy, &d);
	printf("create: r: %d\n", r);
	if (r == 0)
	{
		rdatestr(d, dbuf);
		printf("date: %s\n", dbuf);
	}

	/* input mask is mmddyyyy */
	date_test_strdate("12031994");
	date_test_strdate("9.6.1994");

	date_test_fmt(d, "mmddyy");
	date_test_fmt(d, "ddmmyy");
	date_test_fmt(d, "yymmdd");
	date_test_fmt(d, "yy/mm/dd");
	date_test_fmt(d, "yy mm dd");
	date_test_fmt(d, "yy.mm.dd");
	date_test_fmt(d, ".mm.yyyy.dd.");
	date_test_fmt(d, "mmm. dd, yyyy");
	date_test_fmt(d, "mmm dd yyyy");
	date_test_fmt(d, "yyyy dd mm");
	date_test_fmt(d, "ddd, mmm. dd, yyyy");
	date_test_fmt(d, "(ddd) mmm. dd, yyyy");

	date_test_defmt("ddmmyy", "21-2-54");
	date_test_defmt("ddmmyy", "2-12-54");
	date_test_defmt("ddmmyy", "20111954");
	date_test_defmt("ddmmyy", "130464");
	date_test_defmt("mmm.dd.yyyy", "MAR-12-1967");
	date_test_defmt("yy/mm/dd", "1954, February 3rd");
	date_test_defmt("mmm.dd.yyyy", "041269");
	date_test_defmt("yy/mm/dd", "In the year 2525, in the month of July, mankind will be alive on the 28th day");
	date_test_defmt("dd-mm-yy", "I said on the 28th of July in the year 2525");
	date_test_defmt("mmm.dd.yyyy", "9/14/58");
	date_test_defmt("yy/mm/dd", "47/03/29");
	date_test_defmt("mmm.dd.yyyy", "oct 28 1975");
	date_test_defmt("mmddyy", "Nov 14th, 1985");
	/* ok: still contains dd mm yy */
	date_test_defmt("bladdfoommbaryybong", "20/11/1954");
	/* 1994 is not a leap year, it accepts the date as 01-03-1994 */
	date_test_defmt("ddmmyy", "29-02-1994");

	/* ECPG_INFORMIX_ENOTDMY, need "dd", "mm" and "yy" */
	date_test_defmt("dmy", "20/11/1954");

	/* ECPG_INFORMIX_ENOSHORTDATE */
	date_test_defmt("ddmmyy", "21254");
	date_test_defmt("ddmmyy", "    21254    ");

	/* ECPG_INFORMIX_BAD_DAY */
	date_test_defmt("ddmmyy", "320494");

	/* ECPG_INFORMIX_BAD_MONTH */
	date_test_defmt("mm-yyyy-dd", "13-1993-21");

	/* ECPG_INFORMIX_BAD_YEAR */
	/* ??? */

	return 0;
}