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
struct kmemleak_object {int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int atomic_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_object(struct kmemleak_object *object)
{
	return atomic_inc_not_zero(&object->use_count);
}