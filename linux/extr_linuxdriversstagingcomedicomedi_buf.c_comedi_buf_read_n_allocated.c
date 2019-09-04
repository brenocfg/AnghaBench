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
struct comedi_async {unsigned int buf_read_alloc_count; unsigned int buf_read_count; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int comedi_buf_read_n_allocated(struct comedi_async *async)
{
	return async->buf_read_alloc_count - async->buf_read_count;
}