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
 int /*<<< orphan*/  OUT_OF_MEMORY ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*) ; 

void *
mm_alloc(size_t size)
{
	void	   *ptr = malloc(size);

	if (ptr == NULL)
		mmfatal(OUT_OF_MEMORY, "out of memory");

	return ptr;
}