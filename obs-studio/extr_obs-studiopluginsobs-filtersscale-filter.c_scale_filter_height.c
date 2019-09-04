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
typedef  int /*<<< orphan*/  uint32_t ;
struct scale_filter_data {int /*<<< orphan*/  cy_out; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t scale_filter_height(void *data)
{
	struct scale_filter_data *filter = data;
	return (uint32_t)filter->cy_out;
}