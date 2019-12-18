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
struct TYPE_5__ {int /*<<< orphan*/ * words; int /*<<< orphan*/  nwords; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Bitmapset *
bms_del_members(Bitmapset *a, const Bitmapset *b)
{
	int			shortlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
		return NULL;
	if (b == NULL)
		return a;
	/* Remove b's bits from a; we need never copy */
	shortlen = Min(a->nwords, b->nwords);
	for (i = 0; i < shortlen; i++)
		a->words[i] &= ~b->words[i];
	return a;
}