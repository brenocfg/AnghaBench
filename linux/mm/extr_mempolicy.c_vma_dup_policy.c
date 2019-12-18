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
struct vm_area_struct {struct mempolicy* vm_policy; } ;
struct mempolicy {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int PTR_ERR (struct mempolicy*) ; 
 struct mempolicy* mpol_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

int vma_dup_policy(struct vm_area_struct *src, struct vm_area_struct *dst)
{
	struct mempolicy *pol = mpol_dup(vma_policy(src));

	if (IS_ERR(pol))
		return PTR_ERR(pol);
	dst->vm_policy = pol;
	return 0;
}