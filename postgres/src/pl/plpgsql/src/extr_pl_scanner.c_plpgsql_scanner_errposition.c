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
 int /*<<< orphan*/  internalerrposition (int) ; 
 int internalerrquery (int /*<<< orphan*/ *) ; 
 int pg_mbstrlen_with_len (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * scanorig ; 

int
plpgsql_scanner_errposition(int location)
{
	int			pos;

	if (location < 0 || scanorig == NULL)
		return 0;				/* no-op if location is unknown */

	/* Convert byte offset to character number */
	pos = pg_mbstrlen_with_len(scanorig, location) + 1;
	/* And pass it to the ereport mechanism */
	(void) internalerrposition(pos);
	/* Also pass the function body string */
	return internalerrquery(scanorig);
}