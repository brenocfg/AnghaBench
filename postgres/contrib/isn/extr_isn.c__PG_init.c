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

/* Variables and functions */
 int /*<<< orphan*/  EAN13_index ; 
 int /*<<< orphan*/  EAN13_range ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ISBN_index ; 
 int /*<<< orphan*/  ISBN_range ; 
 int /*<<< orphan*/  ISMN_index ; 
 int /*<<< orphan*/  ISMN_range ; 
 scalar_t__ ISN_DEBUG ; 
 int /*<<< orphan*/  ISSN_index ; 
 int /*<<< orphan*/  ISSN_range ; 
 int /*<<< orphan*/  UPC_index ; 
 int /*<<< orphan*/  UPC_range ; 
 int /*<<< orphan*/  check_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
_PG_init(void)
{
	if (ISN_DEBUG)
	{
		if (!check_table(EAN13_range, EAN13_index))
			elog(ERROR, "EAN13 failed check");
		if (!check_table(ISBN_range, ISBN_index))
			elog(ERROR, "ISBN failed check");
		if (!check_table(ISMN_range, ISMN_index))
			elog(ERROR, "ISMN failed check");
		if (!check_table(ISSN_range, ISSN_index))
			elog(ERROR, "ISSN failed check");
		if (!check_table(UPC_range, UPC_index))
			elog(ERROR, "UPC failed check");
	}
}