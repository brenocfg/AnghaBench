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
struct vars {int /*<<< orphan*/ * treefree; struct subre* treechain; } ;
struct subre {int flags; struct subre* chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct subre*) ; 
 int INUSE ; 

__attribute__((used)) static void
cleanst(struct vars *v)
{
	struct subre *t;
	struct subre *next;

	for (t = v->treechain; t != NULL; t = next)
	{
		next = t->chain;
		if (!(t->flags & INUSE))
			FREE(t);
	}
	v->treechain = NULL;
	v->treefree = NULL;			/* just on general principles */
}