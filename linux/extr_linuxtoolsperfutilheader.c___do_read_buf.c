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
struct feat_fd {scalar_t__ offset; scalar_t__ buf; scalar_t__ size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int __do_read_buf(struct feat_fd *ff, void *addr, ssize_t size)
{
	if (size > (ssize_t)ff->size - ff->offset)
		return -1;

	memcpy(addr, ff->buf + ff->offset, size);
	ff->offset += size;

	return 0;

}