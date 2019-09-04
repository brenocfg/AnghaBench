#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int time; int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {int retrycount; scalar_t__ justid; scalar_t__ force; TYPE_1__ idle; } ;
typedef  TYPE_2__ xclaimOptions ;

/* Variables and functions */

__attribute__((used)) static int xclaim_options_argc(xclaimOptions *opt) {
    int argc = 0;

    if (opt->idle.type != NULL && opt->idle.time != -1)
        argc += 2;
    if (opt->retrycount != -1)
        argc += 2;
    if (opt->force)
        argc++;
    if (opt->justid)
        argc++;

    return argc;
}