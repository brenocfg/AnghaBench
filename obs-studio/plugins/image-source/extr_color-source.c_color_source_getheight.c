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
struct color_source {int /*<<< orphan*/  height; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t color_source_getheight(void *data)
{
	struct color_source *context = data;
	return context->height;
}