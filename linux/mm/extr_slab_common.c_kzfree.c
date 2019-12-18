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
 int /*<<< orphan*/  ZERO_OR_NULL_PTR (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 size_t ksize (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void kzfree(const void *p)
{
	size_t ks;
	void *mem = (void *)p;

	if (unlikely(ZERO_OR_NULL_PTR(mem)))
		return;
	ks = ksize(mem);
	memset(mem, 0, ks);
	kfree(mem);
}