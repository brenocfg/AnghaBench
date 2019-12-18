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
typedef  int /*<<< orphan*/  u32 ;
struct io_rings {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 size_t array_size (int,unsigned int) ; 
 scalar_t__ check_add_overflow (size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  cqes ; 
 size_t struct_size (struct io_rings*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned long rings_size(unsigned sq_entries, unsigned cq_entries,
				size_t *sq_offset)
{
	struct io_rings *rings;
	size_t off, sq_array_size;

	off = struct_size(rings, cqes, cq_entries);
	if (off == SIZE_MAX)
		return SIZE_MAX;

#ifdef CONFIG_SMP
	off = ALIGN(off, SMP_CACHE_BYTES);
	if (off == 0)
		return SIZE_MAX;
#endif

	sq_array_size = array_size(sizeof(u32), sq_entries);
	if (sq_array_size == SIZE_MAX)
		return SIZE_MAX;

	if (check_add_overflow(off, sq_array_size, &off))
		return SIZE_MAX;

	if (sq_offset)
		*sq_offset = off;

	return off;
}