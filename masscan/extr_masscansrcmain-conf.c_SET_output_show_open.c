#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int is_show_open; scalar_t__ is_show_host; scalar_t__ is_show_closed; } ;
struct Masscan {TYPE_1__ output; scalar_t__ echo; } ;

/* Variables and functions */
 int CONF_OK ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 

__attribute__((used)) static int SET_output_show_open(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    UNUSEDPARM(value);
    if (masscan->echo) {
        return 0;
    }
    /* "open" "open-only" */
    masscan->output.is_show_open = 1;
    masscan->output.is_show_closed = 0;
    masscan->output.is_show_host = 0;
    return CONF_OK;
}