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
struct down_root_context {struct down_root_context* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct down_root_context*) ; 

__attribute__((used)) static void
free_context(struct down_root_context *context)
{
    if (context)
    {
        if (context->command)
        {
            free(context->command);
        }
        free(context);
    }
}