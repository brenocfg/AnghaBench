#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vars {struct dfa** ladfas; TYPE_1__* g; } ;
struct subre {int /*<<< orphan*/  cnfa; } ;
struct dfa {int dummy; } ;
struct TYPE_2__ {int nlacons; int /*<<< orphan*/  cmap; struct subre* lacons; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMALLOC ; 
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  assert (int) ; 
 struct dfa* newdfa (struct vars*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dfa *
getladfa(struct vars *v,
		 int n)
{
	assert(n > 0 && n < v->g->nlacons && v->g->lacons != NULL);

	if (v->ladfas[n] == NULL)
	{
		struct subre *sub = &v->g->lacons[n];

		v->ladfas[n] = newdfa(v, &sub->cnfa, &v->g->cmap, DOMALLOC);
		if (ISERR())
			return NULL;
	}
	return v->ladfas[n];
}