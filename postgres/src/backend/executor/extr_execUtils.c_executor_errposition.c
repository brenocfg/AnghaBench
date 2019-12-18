#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * es_sourceText; } ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int errposition (int) ; 
 int pg_mbstrlen_with_len (int /*<<< orphan*/ *,int) ; 

int
executor_errposition(EState *estate, int location)
{
	int			pos;

	/* No-op if location was not provided */
	if (location < 0)
		return 0;
	/* Can't do anything if source text is not available */
	if (estate == NULL || estate->es_sourceText == NULL)
		return 0;
	/* Convert offset to character number */
	pos = pg_mbstrlen_with_len(estate->es_sourceText, location) + 1;
	/* And pass it to the ereport mechanism */
	return errposition(pos);
}