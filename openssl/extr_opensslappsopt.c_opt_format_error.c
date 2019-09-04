#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long retval; scalar_t__ name; } ;
typedef  TYPE_1__ OPT_PAIR ;

/* Variables and functions */
 unsigned long OPT_FMT_PEMDER ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  opt_printf_stderr (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  prog ; 

int opt_format_error(const char *s, unsigned long flags)
{
    OPT_PAIR *ap;

    if (flags == OPT_FMT_PEMDER) {
        opt_printf_stderr("%s: Bad format \"%s\"; must be pem or der\n",
                          prog, s);
    } else {
        opt_printf_stderr("%s: Bad format \"%s\"; must be one of:\n",
                          prog, s);
        for (ap = formats; ap->name; ap++)
            if (flags & ap->retval)
                opt_printf_stderr("   %s\n", ap->name);
    }
    return 0;
}