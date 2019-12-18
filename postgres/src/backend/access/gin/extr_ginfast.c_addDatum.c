#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nvalues; int maxvalues; int /*<<< orphan*/ * categories; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ KeyArray ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
addDatum(KeyArray *keys, Datum datum, GinNullCategory category)
{
	if (keys->nvalues >= keys->maxvalues)
	{
		keys->maxvalues *= 2;
		keys->keys = (Datum *)
			repalloc(keys->keys, sizeof(Datum) * keys->maxvalues);
		keys->categories = (GinNullCategory *)
			repalloc(keys->categories, sizeof(GinNullCategory) * keys->maxvalues);
	}

	keys->keys[keys->nvalues] = datum;
	keys->categories[keys->nvalues] = category;
	keys->nvalues++;
}