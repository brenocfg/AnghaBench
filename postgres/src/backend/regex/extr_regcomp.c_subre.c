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
struct vars {struct subre* treechain; struct subre* treefree; int /*<<< orphan*/  re; } ;
struct subre {int op; int flags; int min; int max; int /*<<< orphan*/  cnfa; struct state* end; struct state* begin; int /*<<< orphan*/ * right; struct subre* left; scalar_t__ subno; scalar_t__ id; struct subre* chain; } ;
struct state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZAPCNFA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,int) ; 

__attribute__((used)) static struct subre *
subre(struct vars *v,
	  int op,
	  int flags,
	  struct state *begin,
	  struct state *end)
{
	struct subre *ret = v->treefree;

	/*
	 * Checking for stack overflow here is sufficient to protect parse() and
	 * its recursive subroutines.
	 */
	if (STACK_TOO_DEEP(v->re))
	{
		ERR(REG_ETOOBIG);
		return NULL;
	}

	if (ret != NULL)
		v->treefree = ret->left;
	else
	{
		ret = (struct subre *) MALLOC(sizeof(struct subre));
		if (ret == NULL)
		{
			ERR(REG_ESPACE);
			return NULL;
		}
		ret->chain = v->treechain;
		v->treechain = ret;
	}

	assert(strchr("=b|.*(", op) != NULL);

	ret->op = op;
	ret->flags = flags;
	ret->id = 0;				/* will be assigned later */
	ret->subno = 0;
	ret->min = ret->max = 1;
	ret->left = NULL;
	ret->right = NULL;
	ret->begin = begin;
	ret->end = end;
	ZAPCNFA(ret->cnfa);

	return ret;
}