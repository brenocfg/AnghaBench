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
struct vars {struct subre* treefree; int /*<<< orphan*/ * treechain; } ;
struct subre {struct subre* left; scalar_t__ flags; int /*<<< orphan*/  cnfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct subre*) ; 
 int /*<<< orphan*/  NULLCNFA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freecnfa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
freesrnode(struct vars *v,		/* might be NULL */
		   struct subre *sr)
{
	if (sr == NULL)
		return;

	if (!NULLCNFA(sr->cnfa))
		freecnfa(&sr->cnfa);
	sr->flags = 0;

	if (v != NULL && v->treechain != NULL)
	{
		/* we're still parsing, maybe we can reuse the subre */
		sr->left = v->treefree;
		v->treefree = sr;
	}
	else
		FREE(sr);
}