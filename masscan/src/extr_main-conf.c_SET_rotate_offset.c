#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int offset; } ;
struct TYPE_3__ {TYPE_2__ rotate; } ;
struct Masscan {TYPE_1__ output; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned int) ; 
 scalar_t__ parseTime (char const*) ; 

__attribute__((used)) static int SET_rotate_offset(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    /* Time offset, otherwise output files are aligned to nearest time
     * interval, e.g. at the start of the hour for "hourly" */
    if (masscan->echo) {
        if (masscan->output.rotate.offset || masscan->echo_all)
            fprintf(masscan->echo, "rotate-offset = %u\n", masscan->output.rotate.offset);
        return 0;
    }
    masscan->output.rotate.offset = (unsigned)parseTime(value);
    return CONF_OK;
}