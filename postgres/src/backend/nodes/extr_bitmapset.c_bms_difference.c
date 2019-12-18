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
struct TYPE_7__ {int /*<<< orphan*/ * words; int /*<<< orphan*/  nwords; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bms_copy (TYPE_1__ const*) ; 

Bitmapset *
bms_difference(const Bitmapset *a, const Bitmapset *b)
{
	Bitmapset  *result;
	int			shortlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
		return NULL;
	if (b == NULL)
		return bms_copy(a);
	/* Copy the left input */
	result = bms_copy(a);
	/* And remove b's bits from result */
	shortlen = Min(a->nwords, b->nwords);
	for (i = 0; i < shortlen; i++)
		result->words[i] &= ~b->words[i];
	return result;
}