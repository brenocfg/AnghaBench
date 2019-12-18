#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* words; int /*<<< orphan*/  nwords; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
bms_overlap(const Bitmapset *a, const Bitmapset *b)
{
	int			shortlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL || b == NULL)
		return false;
	/* Check words in common */
	shortlen = Min(a->nwords, b->nwords);
	for (i = 0; i < shortlen; i++)
	{
		if ((a->words[i] & b->words[i]) != 0)
			return true;
	}
	return false;
}