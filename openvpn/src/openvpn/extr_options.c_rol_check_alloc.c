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
struct options {int /*<<< orphan*/  gc; scalar_t__ routes; } ;

/* Variables and functions */
 scalar_t__ new_route_option_list (int /*<<< orphan*/ *) ; 

void
rol_check_alloc(struct options *options)
{
    if (!options->routes)
    {
        options->routes = new_route_option_list(&options->gc);
    }
}