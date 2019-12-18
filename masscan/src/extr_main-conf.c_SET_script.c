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
struct TYPE_2__ {char* name; } ;
struct Masscan {int is_scripting; TYPE_1__ scripting; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int SET_script(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    if (masscan->echo) {
        if ((masscan->scripting.name && masscan->scripting.name[0]) || masscan->echo_all)
            fprintf(masscan->echo, "script = %s\n", masscan->scripting.name);
        return 0;
    }
    if (value && value[0])
        masscan->is_scripting = 1;
    else
        masscan->is_scripting = 0;
    
    if (masscan->scripting.name)
        free(masscan->scripting.name);
    
    masscan->scripting.name = strdup(value);
    
    return CONF_OK;
}