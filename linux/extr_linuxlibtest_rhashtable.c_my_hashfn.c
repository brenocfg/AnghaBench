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
typedef  int u32 ;
struct TYPE_2__ {int id; } ;
struct test_obj_rhl {TYPE_1__ value; } ;

/* Variables and functions */

__attribute__((used)) static u32 my_hashfn(const void *data, u32 len, u32 seed)
{
	const struct test_obj_rhl *obj = data;

	return (obj->value.id % 10);
}