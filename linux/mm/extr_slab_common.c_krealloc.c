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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* ZERO_SIZE_PTR ; 
 void* __do_krealloc (void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ kasan_reset_tag (void*) ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 scalar_t__ unlikely (int) ; 

void *krealloc(const void *p, size_t new_size, gfp_t flags)
{
	void *ret;

	if (unlikely(!new_size)) {
		kfree(p);
		return ZERO_SIZE_PTR;
	}

	ret = __do_krealloc(p, new_size, flags);
	if (ret && kasan_reset_tag(p) != kasan_reset_tag(ret))
		kfree(p);

	return ret;
}