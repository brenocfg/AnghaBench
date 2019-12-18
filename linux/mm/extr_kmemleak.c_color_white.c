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
struct kmemleak_object {scalar_t__ count; scalar_t__ min_count; } ;

/* Variables and functions */
 scalar_t__ KMEMLEAK_BLACK ; 

__attribute__((used)) static bool color_white(const struct kmemleak_object *object)
{
	return object->count != KMEMLEAK_BLACK &&
		object->count < object->min_count;
}