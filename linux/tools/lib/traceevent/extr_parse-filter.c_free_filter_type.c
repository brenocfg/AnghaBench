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
struct tep_filter_type {int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_arg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_filter_type(struct tep_filter_type *filter_type)
{
	free_arg(filter_type->filter);
}