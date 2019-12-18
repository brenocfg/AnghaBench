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
struct xyarray {size_t entry_size; size_t row_size; int entries; int max_x; int max_y; } ;

/* Variables and functions */
 struct xyarray* zalloc (int) ; 

struct xyarray *xyarray__new(int xlen, int ylen, size_t entry_size)
{
	size_t row_size = ylen * entry_size;
	struct xyarray *xy = zalloc(sizeof(*xy) + xlen * row_size);

	if (xy != NULL) {
		xy->entry_size = entry_size;
		xy->row_size   = row_size;
		xy->entries    = xlen * ylen;
		xy->max_x      = xlen;
		xy->max_y      = ylen;
	}

	return xy;
}