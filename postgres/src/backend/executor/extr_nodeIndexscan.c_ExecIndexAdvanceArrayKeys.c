#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int next_elem; int num_elems; int* elem_nulls; int /*<<< orphan*/ * elem_values; TYPE_1__* scan_key; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_flags; int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  TYPE_2__ IndexArrayKeyInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  SK_ISNULL ; 

bool
ExecIndexAdvanceArrayKeys(IndexArrayKeyInfo *arrayKeys, int numArrayKeys)
{
	bool		found = false;
	int			j;

	/*
	 * Note we advance the rightmost array key most quickly, since it will
	 * correspond to the lowest-order index column among the available
	 * qualifications.  This is hypothesized to result in better locality of
	 * access in the index.
	 */
	for (j = numArrayKeys - 1; j >= 0; j--)
	{
		ScanKey		scan_key = arrayKeys[j].scan_key;
		int			next_elem = arrayKeys[j].next_elem;
		int			num_elems = arrayKeys[j].num_elems;
		Datum	   *elem_values = arrayKeys[j].elem_values;
		bool	   *elem_nulls = arrayKeys[j].elem_nulls;

		if (next_elem >= num_elems)
		{
			next_elem = 0;
			found = false;		/* need to advance next array key */
		}
		else
			found = true;
		scan_key->sk_argument = elem_values[next_elem];
		if (elem_nulls[next_elem])
			scan_key->sk_flags |= SK_ISNULL;
		else
			scan_key->sk_flags &= ~SK_ISNULL;
		arrayKeys[j].next_elem = next_elem + 1;
		if (found)
			break;
	}

	return found;
}