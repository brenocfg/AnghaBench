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
struct subre {struct subre* right; struct subre* left; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INUSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
markst(struct subre *t)
{
	assert(t != NULL);

	t->flags |= INUSE;
	if (t->left != NULL)
		markst(t->left);
	if (t->right != NULL)
		markst(t->right);
}