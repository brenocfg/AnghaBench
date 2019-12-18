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
struct TYPE_3__ {char* sort_value; int rank; } ;
typedef  TYPE_1__ pivot_field ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  pg_free (int*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rankCompare ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static void
rankSort(int num_columns, pivot_field *piv_columns)
{
	int		   *hmap;			/* [[offset in piv_columns, rank], ...for
								 * every header entry] */
	int			i;

	hmap = (int *) pg_malloc(sizeof(int) * num_columns * 2);
	for (i = 0; i < num_columns; i++)
	{
		char	   *val = piv_columns[i].sort_value;

		/* ranking information is valid if non null and matches /^-?\d+$/ */
		if (val &&
			((*val == '-' &&
			  strspn(val + 1, "0123456789") == strlen(val + 1)) ||
			 strspn(val, "0123456789") == strlen(val)))
		{
			hmap[i * 2] = atoi(val);
			hmap[i * 2 + 1] = i;
		}
		else
		{
			/* invalid rank information ignored (equivalent to rank 0) */
			hmap[i * 2] = 0;
			hmap[i * 2 + 1] = i;
		}
	}

	qsort(hmap, num_columns, sizeof(int) * 2, rankCompare);

	for (i = 0; i < num_columns; i++)
	{
		piv_columns[hmap[i * 2 + 1]].rank = i;
	}

	pg_free(hmap);
}