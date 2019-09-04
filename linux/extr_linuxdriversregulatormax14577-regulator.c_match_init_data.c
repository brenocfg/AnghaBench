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
struct regulator_init_data {int dummy; } ;
typedef  enum maxim_device_type { ____Placeholder_maxim_device_type } maxim_device_type ;

/* Variables and functions */

__attribute__((used)) static inline struct regulator_init_data *match_init_data(int index,
		enum maxim_device_type dev_type)
{
	return NULL;
}