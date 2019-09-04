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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __vmalloc (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *vmalloc_32(unsigned long size)
{
	return __vmalloc(size, GFP_KERNEL, PAGE_KERNEL);
}