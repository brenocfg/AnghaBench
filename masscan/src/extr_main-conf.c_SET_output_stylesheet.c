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
struct TYPE_2__ {char* stylesheet; scalar_t__ format; } ;
struct Masscan {TYPE_1__ output; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 scalar_t__ Output_XML ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  strcpy_s (char*,int,char const*) ; 

__attribute__((used)) static int SET_output_stylesheet(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    if (masscan->echo) {
        if (masscan->output.stylesheet[0] || masscan->echo_all)
            fprintf(masscan->echo, "stylesheet = %s\n", masscan->output.stylesheet);
        return 0;
    }
    
    if (masscan->output.format == 0)
        masscan->output.format = Output_XML;
    
    strcpy_s(masscan->output.stylesheet, sizeof(masscan->output.stylesheet), value);
    return CONF_OK;
}