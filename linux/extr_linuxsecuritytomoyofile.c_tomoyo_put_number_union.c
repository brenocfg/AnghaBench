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
struct tomoyo_number_union {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_put_group (int /*<<< orphan*/ ) ; 

void tomoyo_put_number_union(struct tomoyo_number_union *ptr)
{
	tomoyo_put_group(ptr->group);
}