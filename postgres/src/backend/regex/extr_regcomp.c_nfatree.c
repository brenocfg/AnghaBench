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
struct vars {int dummy; } ;
struct subre {struct subre* right; struct subre* left; int /*<<< orphan*/ * begin; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DISCARD ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 long nfanode (struct vars*,struct subre*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long						/* optimize results from top node */
nfatree(struct vars *v,
		struct subre *t,
		FILE *f)				/* for debug output */
{
	assert(t != NULL && t->begin != NULL);

	if (t->left != NULL)
		(DISCARD) nfatree(v, t->left, f);
	if (t->right != NULL)
		(DISCARD) nfatree(v, t->right, f);

	return nfanode(v, t, 0, f);
}