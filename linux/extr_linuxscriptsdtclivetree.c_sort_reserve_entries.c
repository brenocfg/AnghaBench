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
struct reserve_info {struct reserve_info* next; } ;
struct dt_info {struct reserve_info* reservelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_reserve_info ; 
 int /*<<< orphan*/  free (struct reserve_info**) ; 
 int /*<<< orphan*/  qsort (struct reserve_info**,int,int,int /*<<< orphan*/ ) ; 
 struct reserve_info** xmalloc (int) ; 

__attribute__((used)) static void sort_reserve_entries(struct dt_info *dti)
{
	struct reserve_info *ri, **tbl;
	int n = 0, i = 0;

	for (ri = dti->reservelist;
	     ri;
	     ri = ri->next)
		n++;

	if (n == 0)
		return;

	tbl = xmalloc(n * sizeof(*tbl));

	for (ri = dti->reservelist;
	     ri;
	     ri = ri->next)
		tbl[i++] = ri;

	qsort(tbl, n, sizeof(*tbl), cmp_reserve_info);

	dti->reservelist = tbl[0];
	for (i = 0; i < (n-1); i++)
		tbl[i]->next = tbl[i+1];
	tbl[n-1]->next = NULL;

	free(tbl);
}