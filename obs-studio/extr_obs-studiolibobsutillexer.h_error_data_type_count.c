#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; TYPE_1__* array; } ;
struct error_data {TYPE_2__ errors; } ;
struct TYPE_3__ {int level; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t error_data_type_count(struct error_data *ed,
		int type)
{
	size_t count = 0, i;
	for (i = 0; i < ed->errors.num; i++) {
		if (ed->errors.array[i].level == type)
			count++;
	}

	return count;
}