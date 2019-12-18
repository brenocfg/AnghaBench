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
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_COMP ; 
 int __GFP_HIGHMEM ; 
 void* kmalloc (unsigned long,int) ; 

void *__vmalloc(unsigned long size, gfp_t gfp_mask, pgprot_t prot)
{
	/*
	 *  You can't specify __GFP_HIGHMEM with kmalloc() since kmalloc()
	 * returns only a logical address.
	 */
	return kmalloc(size, (gfp_mask | __GFP_COMP) & ~__GFP_HIGHMEM);
}