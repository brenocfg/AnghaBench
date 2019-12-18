#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nwords; scalar_t__* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int bms_is_empty (TYPE_1__ const*) ; 

bool
bms_equal(const Bitmapset *a, const Bitmapset *b)
{
	const Bitmapset *shorter;
	const Bitmapset *longer;
	int			shortlen;
	int			longlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
	{
		if (b == NULL)
			return true;
		return bms_is_empty(b);
	}
	else if (b == NULL)
		return bms_is_empty(a);
	/* Identify shorter and longer input */
	if (a->nwords <= b->nwords)
	{
		shorter = a;
		longer = b;
	}
	else
	{
		shorter = b;
		longer = a;
	}
	/* And process */
	shortlen = shorter->nwords;
	for (i = 0; i < shortlen; i++)
	{
		if (shorter->words[i] != longer->words[i])
			return false;
	}
	longlen = longer->nwords;
	for (; i < longlen; i++)
	{
		if (longer->words[i] != 0)
			return false;
	}
	return true;
}