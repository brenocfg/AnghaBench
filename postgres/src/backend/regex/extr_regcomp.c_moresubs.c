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
struct vars {size_t nsubs; struct subre** subs; struct subre** sub10; } ;
struct subre {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MALLOC (size_t) ; 
 scalar_t__ REALLOC (struct subre**,size_t) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  VS (struct subre**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
moresubs(struct vars *v,
		 int wanted)			/* want enough room for this one */
{
	struct subre **p;
	size_t		n;

	assert(wanted > 0 && (size_t) wanted >= v->nsubs);
	n = (size_t) wanted * 3 / 2 + 1;

	if (v->subs == v->sub10)
	{
		p = (struct subre **) MALLOC(n * sizeof(struct subre *));
		if (p != NULL)
			memcpy(VS(p), VS(v->subs),
				   v->nsubs * sizeof(struct subre *));
	}
	else
		p = (struct subre **) REALLOC(v->subs, n * sizeof(struct subre *));
	if (p == NULL)
	{
		ERR(REG_ESPACE);
		return;
	}
	v->subs = p;
	for (p = &v->subs[v->nsubs]; v->nsubs < n; p++, v->nsubs++)
		*p = NULL;
	assert(v->nsubs == n);
	assert((size_t) wanted < v->nsubs);
}