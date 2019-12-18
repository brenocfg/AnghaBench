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
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  memory_exhausted (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
size_product(size_t nitems, size_t itemsize)
{
	if (SIZE_MAX / itemsize < nitems)
		memory_exhausted(_("size overflow"));
	return nitems * itemsize;
}