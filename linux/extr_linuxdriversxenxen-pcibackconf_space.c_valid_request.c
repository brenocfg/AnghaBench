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

__attribute__((used)) static inline int valid_request(int offset, int size)
{
	/* Validate request (no un-aligned requests) */
	if ((size == 1 || size == 2 || size == 4) && (offset % size) == 0)
		return 1;
	return 0;
}