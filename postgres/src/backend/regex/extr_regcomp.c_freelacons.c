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
struct subre {int /*<<< orphan*/  cnfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct subre*) ; 
 int /*<<< orphan*/  NULLCNFA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freecnfa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
freelacons(struct subre *subs,
		   int n)
{
	struct subre *sub;
	int			i;

	assert(n > 0);
	for (sub = subs + 1, i = n - 1; i > 0; sub++, i--)	/* no 0th */
		if (!NULLCNFA(sub->cnfa))
			freecnfa(&sub->cnfa);
	FREE(subs);
}