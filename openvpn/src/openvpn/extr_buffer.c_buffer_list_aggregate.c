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
struct buffer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_list_aggregate_separator (struct buffer_list*,size_t const,char*) ; 

void
buffer_list_aggregate(struct buffer_list *bl, const size_t max)
{
    buffer_list_aggregate_separator(bl, max, "");
}