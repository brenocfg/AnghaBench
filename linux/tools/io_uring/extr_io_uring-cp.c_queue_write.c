#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct io_uring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_len; struct io_data* iov_base; } ;
struct io_data {int /*<<< orphan*/  first_len; TYPE_1__ iov; int /*<<< orphan*/  first_offset; int /*<<< orphan*/  offset; scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_uring_submit (struct io_uring*) ; 
 int /*<<< orphan*/  queue_prepped (struct io_uring*,struct io_data*) ; 

__attribute__((used)) static void queue_write(struct io_uring *ring, struct io_data *data)
{
	data->read = 0;
	data->offset = data->first_offset;

	data->iov.iov_base = data + 1;
	data->iov.iov_len = data->first_len;

	queue_prepped(ring, data);
	io_uring_submit(ring);
}