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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 struct scatterlist* sgl_alloc_order (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int*) ; 

int
target_alloc_sgl(struct scatterlist **sgl, unsigned int *nents, u32 length,
		 bool zero_page, bool chainable)
{
	gfp_t gfp = GFP_KERNEL | (zero_page ? __GFP_ZERO : 0);

	*sgl = sgl_alloc_order(length, 0, chainable, gfp, nents);
	return *sgl ? 0 : -ENOMEM;
}