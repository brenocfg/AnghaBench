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
struct vars {int nlacons; struct subre* lacons; } ;
struct subre {int subno; int /*<<< orphan*/  cnfa; struct state* end; struct state* begin; } ;
struct state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MALLOC (int) ; 
 scalar_t__ REALLOC (struct subre*,int) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  ZAPCNFA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int						/* lacon number */
newlacon(struct vars *v,
		 struct state *begin,
		 struct state *end,
		 int latype)
{
	int			n;
	struct subre *newlacons;
	struct subre *sub;

	if (v->nlacons == 0)
	{
		n = 1;					/* skip 0th */
		newlacons = (struct subre *) MALLOC(2 * sizeof(struct subre));
	}
	else
	{
		n = v->nlacons;
		newlacons = (struct subre *) REALLOC(v->lacons,
											 (n + 1) * sizeof(struct subre));
	}
	if (newlacons == NULL)
	{
		ERR(REG_ESPACE);
		return 0;
	}
	v->lacons = newlacons;
	v->nlacons = n + 1;
	sub = &v->lacons[n];
	sub->begin = begin;
	sub->end = end;
	sub->subno = latype;
	ZAPCNFA(sub->cnfa);
	return n;
}