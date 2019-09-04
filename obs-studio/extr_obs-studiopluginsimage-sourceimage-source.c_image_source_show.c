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
struct image_source {int /*<<< orphan*/  persistent; } ;

/* Variables and functions */
 int /*<<< orphan*/  image_source_load (struct image_source*) ; 

__attribute__((used)) static void image_source_show(void *data)
{
	struct image_source *context = data;

	if (!context->persistent)
		image_source_load(context);
}