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
struct TYPE_6__ {scalar_t__ nwords; int /*<<< orphan*/ * words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

Bitmapset *
bms_join(Bitmapset *a, Bitmapset *b)
{
	Bitmapset  *result;
	Bitmapset  *other;
	int			otherlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	/* Identify shorter and longer input; use longer one as result */
	if (a->nwords < b->nwords)
	{
		result = b;
		other = a;
	}
	else
	{
		result = a;
		other = b;
	}
	/* And union the shorter input into the result */
	otherlen = other->nwords;
	for (i = 0; i < otherlen; i++)
		result->words[i] |= other->words[i];
	if (other != result)		/* pure paranoia */
		pfree(other);
	return result;
}