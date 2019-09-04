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
struct mic_copy_desc {unsigned int iovcnt; TYPE_1__* iov; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static ssize_t
sum_iovec_len(struct mic_copy_desc *copy)
{
	ssize_t sum = 0;
	unsigned int i;

	for (i = 0; i < copy->iovcnt; i++)
		sum += copy->iov[i].iov_len;
	return sum;
}