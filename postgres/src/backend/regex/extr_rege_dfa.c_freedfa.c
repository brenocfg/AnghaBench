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
struct dfa {int /*<<< orphan*/ * mallocarea; int /*<<< orphan*/ * incarea; int /*<<< orphan*/ * outsarea; int /*<<< orphan*/ * statesarea; int /*<<< orphan*/ * ssets; scalar_t__ cptsmalloced; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
freedfa(struct dfa *d)
{
	if (d->cptsmalloced)
	{
		if (d->ssets != NULL)
			FREE(d->ssets);
		if (d->statesarea != NULL)
			FREE(d->statesarea);
		if (d->outsarea != NULL)
			FREE(d->outsarea);
		if (d->incarea != NULL)
			FREE(d->incarea);
	}

	if (d->mallocarea != NULL)
		FREE(d->mallocarea);
}