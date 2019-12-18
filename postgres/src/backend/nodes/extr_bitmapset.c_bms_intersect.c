#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nwords; int /*<<< orphan*/ * words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 TYPE_1__* bms_copy (TYPE_1__ const*) ; 

Bitmapset *
bms_intersect(const Bitmapset *a, const Bitmapset *b)
{
	Bitmapset  *result;
	const Bitmapset *other;
	int			resultlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL || b == NULL)
		return NULL;
	/* Identify shorter and longer input; copy the shorter one */
	if (a->nwords <= b->nwords)
	{
		result = bms_copy(a);
		other = b;
	}
	else
	{
		result = bms_copy(b);
		other = a;
	}
	/* And intersect the longer input with the result */
	resultlen = result->nwords;
	for (i = 0; i < resultlen; i++)
		result->words[i] &= other->words[i];
	return result;
}