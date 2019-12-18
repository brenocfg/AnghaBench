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
 void* kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static void *kvmemdup(const void *src, size_t len)
{
	void *p = kvmalloc(len, GFP_KERNEL);

	if (p)
		memcpy(p, src, len);
	return p;
}