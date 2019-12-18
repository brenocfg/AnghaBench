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
struct vars {struct dfa** subdfas; TYPE_1__* g; } ;
struct subre {size_t id; int /*<<< orphan*/  cnfa; } ;
struct dfa {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMALLOC ; 
 scalar_t__ ISERR () ; 
 struct dfa* newdfa (struct vars*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dfa *
getsubdfa(struct vars *v,
		  struct subre *t)
{
	if (v->subdfas[t->id] == NULL)
	{
		v->subdfas[t->id] = newdfa(v, &t->cnfa, &v->g->cmap, DOMALLOC);
		if (ISERR())
			return NULL;
	}
	return v->subdfas[t->id];
}