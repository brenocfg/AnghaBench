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
 void* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_run_data(void **data_ptr, unsigned int size_out)
{
	*data_ptr = calloc(size_out, 1);
	if (!*data_ptr) {
		p_err("failed to allocate memory for output data/ctx: %s",
		      strerror(errno));
		return -1;
	}

	return 0;
}