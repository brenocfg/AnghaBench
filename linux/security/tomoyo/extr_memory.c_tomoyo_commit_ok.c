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
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,unsigned int const) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int const) ; 
 scalar_t__ tomoyo_memory_ok (void*) ; 

void *tomoyo_commit_ok(void *data, const unsigned int size)
{
	void *ptr = kzalloc(size, GFP_NOFS);

	if (tomoyo_memory_ok(ptr)) {
		memmove(ptr, data, size);
		memset(data, 0, size);
		return ptr;
	}
	kfree(ptr);
	return NULL;
}