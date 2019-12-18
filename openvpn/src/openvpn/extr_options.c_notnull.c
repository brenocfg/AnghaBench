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

/* Variables and functions */
 int /*<<< orphan*/  M_USAGE ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 

void
notnull(const char *arg, const char *description)
{
    if (!arg)
    {
        msg(M_USAGE, "You must define %s", description);
    }
}