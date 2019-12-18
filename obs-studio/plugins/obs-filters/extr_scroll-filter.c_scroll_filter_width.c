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
struct scroll_filter_data {int /*<<< orphan*/  cx; scalar_t__ limit_cx; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_filter_get_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_get_base_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t scroll_filter_width(void *data)
{
	struct scroll_filter_data *filter = data;
	obs_source_t *target = obs_filter_get_target(filter->context);

	return filter->limit_cx ? filter->cx
				: obs_source_get_base_width(target);
}