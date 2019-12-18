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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  atooid (char const*) ; 
 scalar_t__ palloc (int) ; 
 char* pg_strtok (int*) ; 

Oid *
readOidCols(int numCols)
{
	int			tokenLength,
				i;
	const char *token;
	Oid		   *oid_vals;

	if (numCols <= 0)
		return NULL;

	oid_vals = (Oid *) palloc(numCols * sizeof(Oid));
	for (i = 0; i < numCols; i++)
	{
		token = pg_strtok(&tokenLength);
		oid_vals[i] = atooid(token);
	}

	return oid_vals;
}