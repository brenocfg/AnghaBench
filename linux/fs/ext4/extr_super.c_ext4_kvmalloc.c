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
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_NOWARN ; 
 void* __vmalloc (size_t,int,int /*<<< orphan*/ ) ; 
 void* kmalloc (size_t,int) ; 

void *ext4_kvmalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kmalloc(size, flags | __GFP_NOWARN);
	if (!ret)
		ret = __vmalloc(size, flags, PAGE_KERNEL);
	return ret;
}