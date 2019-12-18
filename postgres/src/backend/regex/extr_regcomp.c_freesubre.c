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
struct subre {struct subre* right; struct subre* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  freesrnode (struct vars*,struct subre*) ; 

__attribute__((used)) static void
freesubre(struct vars *v,		/* might be NULL */
		  struct subre *sr)
{
	if (sr == NULL)
		return;

	if (sr->left != NULL)
		freesubre(v, sr->left);
	if (sr->right != NULL)
		freesubre(v, sr->right);

	freesrnode(v, sr);
}