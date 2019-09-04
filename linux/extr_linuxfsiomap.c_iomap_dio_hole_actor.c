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
struct TYPE_2__ {int /*<<< orphan*/  iter; } ;
struct iomap_dio {int /*<<< orphan*/  size; TYPE_1__ submit; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ iov_iter_zero (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t
iomap_dio_hole_actor(loff_t length, struct iomap_dio *dio)
{
	length = iov_iter_zero(length, dio->submit.iter);
	dio->size += length;
	return length;
}