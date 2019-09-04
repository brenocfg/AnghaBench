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
struct Masscan {scalar_t__ is_noreset; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 scalar_t__ parseBoolean (char const*) ; 

__attribute__((used)) static int SET_noreset(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    if (masscan->echo) {
        if (masscan->is_noreset || masscan->echo_all)
            fprintf(masscan->echo, "noreset = %s\n", masscan->is_noreset?"true":"false");
        return 0;
    }
    masscan->is_noreset = parseBoolean(value);
    return CONF_OK;
}