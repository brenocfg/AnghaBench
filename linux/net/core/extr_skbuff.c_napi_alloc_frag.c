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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int SKB_DATA_ALIGN (unsigned int) ; 
 void* __napi_alloc_frag (unsigned int,int /*<<< orphan*/ ) ; 

void *napi_alloc_frag(unsigned int fragsz)
{
	fragsz = SKB_DATA_ALIGN(fragsz);

	return __napi_alloc_frag(fragsz, GFP_ATOMIC);
}