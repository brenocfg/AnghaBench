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
 int /*<<< orphan*/  buffer_list_reset (struct buffer_list*) ; 
 int /*<<< orphan*/  free (struct buffer_list*) ; 

void
buffer_list_free(struct buffer_list *ol)
{
    if (ol)
    {
        buffer_list_reset(ol);
        free(ol);
    }
}