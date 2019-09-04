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
struct gb_operation {void* private; } ;

/* Variables and functions */

__attribute__((used)) static inline void gb_operation_set_data(struct gb_operation *operation,
					 void *data)
{
	operation->private = data;
}