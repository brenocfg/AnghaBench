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
typedef  int (* qsort_arg_comparator ) (char*,void*,void*) ;

/* Variables and functions */
 size_t Min (int,int) ; 
 int /*<<< orphan*/  SWAPINIT (void*,size_t) ; 
 char* med3 (char*,char*,char*,int (*) (char*,void*,void*),void*) ; 
 int /*<<< orphan*/  swap (char*,char*) ; 
 int /*<<< orphan*/  vecswap (char*,char*,size_t) ; 

void
qsort_arg(void *a, size_t n, size_t es, qsort_arg_comparator cmp, void *arg)
{
	char	   *pa,
			   *pb,
			   *pc,
			   *pd,
			   *pl,
			   *pm,
			   *pn;
	size_t		d1,
				d2;
	int			r,
				swaptype,
				presorted;

loop:SWAPINIT(a, es);
	if (n < 7)
	{
		for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl, arg) > 0;
				 pl -= es)
				swap(pl, pl - es);
		return;
	}
	presorted = 1;
	for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
	{
		if (cmp(pm - es, pm, arg) > 0)
		{
			presorted = 0;
			break;
		}
	}
	if (presorted)
		return;
	pm = (char *) a + (n / 2) * es;
	if (n > 7)
	{
		pl = (char *) a;
		pn = (char *) a + (n - 1) * es;
		if (n > 40)
		{
			size_t		d = (n / 8) * es;

			pl = med3(pl, pl + d, pl + 2 * d, cmp, arg);
			pm = med3(pm - d, pm, pm + d, cmp, arg);
			pn = med3(pn - 2 * d, pn - d, pn, cmp, arg);
		}
		pm = med3(pl, pm, pn, cmp, arg);
	}
	swap(a, pm);
	pa = pb = (char *) a + es;
	pc = pd = (char *) a + (n - 1) * es;
	for (;;)
	{
		while (pb <= pc && (r = cmp(pb, a, arg)) <= 0)
		{
			if (r == 0)
			{
				swap(pa, pb);
				pa += es;
			}
			pb += es;
		}
		while (pb <= pc && (r = cmp(pc, a, arg)) >= 0)
		{
			if (r == 0)
			{
				swap(pc, pd);
				pd -= es;
			}
			pc -= es;
		}
		if (pb > pc)
			break;
		swap(pb, pc);
		pb += es;
		pc -= es;
	}
	pn = (char *) a + n * es;
	d1 = Min(pa - (char *) a, pb - pa);
	vecswap(a, pb - d1, d1);
	d1 = Min(pd - pc, pn - pd - es);
	vecswap(pb, pn - d1, d1);
	d1 = pb - pa;
	d2 = pd - pc;
	if (d1 <= d2)
	{
		/* Recurse on left partition, then iterate on right partition */
		if (d1 > es)
			qsort_arg(a, d1 / es, es, cmp, arg);
		if (d2 > es)
		{
			/* Iterate rather than recurse to save stack space */
			/* qsort_arg(pn - d2, d2 / es, es, cmp, arg); */
			a = pn - d2;
			n = d2 / es;
			goto loop;
		}
	}
	else
	{
		/* Recurse on right partition, then iterate on left partition */
		if (d2 > es)
			qsort_arg(pn - d2, d2 / es, es, cmp, arg);
		if (d1 > es)
		{
			/* Iterate rather than recurse to save stack space */
			/* qsort_arg(a, d1 / es, es, cmp, arg); */
			n = d1 / es;
			goto loop;
		}
	}
}