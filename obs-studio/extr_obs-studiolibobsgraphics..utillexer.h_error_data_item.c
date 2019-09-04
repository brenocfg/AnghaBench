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
struct error_item {int dummy; } ;
struct TYPE_2__ {struct error_item const* array; } ;
struct error_data {TYPE_1__ errors; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct error_item *error_data_item(struct error_data *ed,
		size_t idx)
{
	return ed->errors.array+idx;
}