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
typedef  int /*<<< orphan*/  mbcharacter_incrementer ;

/* Variables and functions */
 int GetDatabaseEncoding () ; 
#define  PG_EUC_JP 129 
#define  PG_UTF8 128 
 int /*<<< orphan*/  pg_eucjp_increment ; 
 int /*<<< orphan*/  pg_generic_charinc ; 
 int /*<<< orphan*/  pg_utf8_increment ; 

mbcharacter_incrementer
pg_database_encoding_character_incrementer(void)
{
	/*
	 * Eventually it might be best to add a field to pg_wchar_table[], but for
	 * now we just use a switch.
	 */
	switch (GetDatabaseEncoding())
	{
		case PG_UTF8:
			return pg_utf8_increment;

		case PG_EUC_JP:
			return pg_eucjp_increment;

		default:
			return pg_generic_charinc;
	}
}