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
struct subre {short id; struct subre* right; struct subre* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int						/* next number */
numst(struct subre *t,
	  int start)				/* starting point for subtree numbers */
{
	int			i;

	assert(t != NULL);

	i = start;
	t->id = (short) i++;
	if (t->left != NULL)
		i = numst(t->left, i);
	if (t->right != NULL)
		i = numst(t->right, i);
	return i;
}