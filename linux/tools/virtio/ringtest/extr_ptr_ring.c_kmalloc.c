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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 void* memalign (int,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void *kmalloc(unsigned size, gfp_t gfp)
{
	void *p = memalign(64, size);
	if (!p)
		return p;

	if (gfp & __GFP_ZERO)
		memset(p, 0, size);
	return p;
}