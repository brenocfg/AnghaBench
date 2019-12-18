#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nwords; int /*<<< orphan*/ * words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int Min (int,int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

Bitmapset *
bms_int_members(Bitmapset *a, const Bitmapset *b)
{
	int			shortlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
		return NULL;
	if (b == NULL)
	{
		pfree(a);
		return NULL;
	}
	/* Intersect b into a; we need never copy */
	shortlen = Min(a->nwords, b->nwords);
	for (i = 0; i < shortlen; i++)
		a->words[i] &= b->words[i];
	for (; i < a->nwords; i++)
		a->words[i] = 0;
	return a;
}