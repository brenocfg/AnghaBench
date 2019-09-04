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
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;

/* Variables and functions */

__attribute__((used)) static inline size_t
calc_stride(size_t size)
{
	/* Allow room for the header */
	size += sizeof(VCHIQ_HEADER_T);

	/* Round up */
	return (size + sizeof(VCHIQ_HEADER_T) - 1) & ~(sizeof(VCHIQ_HEADER_T)
		- 1);
}