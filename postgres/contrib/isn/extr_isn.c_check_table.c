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
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static bool
check_table(const char *(*TABLE)[2], const unsigned TABLE_index[10][2])
{
	const char *aux1,
			   *aux2;
	int			a,
				b,
				x = 0,
				y = -1,
				i = 0,
				j,
				init = 0;

	if (TABLE == NULL || TABLE_index == NULL)
		return true;

	while (TABLE[i][0] && TABLE[i][1])
	{
		aux1 = TABLE[i][0];
		aux2 = TABLE[i][1];

		/* must always start with a digit: */
		if (!isdigit((unsigned char) *aux1) || !isdigit((unsigned char) *aux2))
			goto invalidtable;
		a = *aux1 - '0';
		b = *aux2 - '0';

		/* must always have the same format and length: */
		while (*aux1 && *aux2)
		{
			if (!(isdigit((unsigned char) *aux1) &&
				  isdigit((unsigned char) *aux2)) &&
				(*aux1 != *aux2 || *aux1 != '-'))
				goto invalidtable;
			aux1++;
			aux2++;
		}
		if (*aux1 != *aux2)
			goto invalidtable;

		/* found a new range */
		if (a > y)
		{
			/* check current range in the index: */
			for (j = x; j <= y; j++)
			{
				if (TABLE_index[j][0] != init)
					goto invalidindex;
				if (TABLE_index[j][1] != i - init)
					goto invalidindex;
			}
			init = i;
			x = a;
		}

		/* Always get the new limit */
		y = b;
		if (y < x)
			goto invalidtable;
		i++;
	}

	return true;

invalidtable:
	elog(DEBUG1, "invalid table near {\"%s\", \"%s\"} (pos: %d)",
		 TABLE[i][0], TABLE[i][1], i);
	return false;

invalidindex:
	elog(DEBUG1, "index %d is invalid", j);
	return false;
}