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
struct TYPE_2__ {int is_show_open; int is_show_closed; int is_show_host; } ;
struct Masscan {TYPE_1__ output; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 scalar_t__ EQUALSx (char*,char const*,unsigned int) ; 
 unsigned int INDEX_OF (char const*,char) ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,unsigned int,char const*) ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,char*,char*) ; 

__attribute__((used)) static int SET_output_show(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    if (masscan->echo) {
        if (masscan->echo_all) {
            fprintf(masscan->echo, "output-show = %s%s%s\n",
                    masscan->output.is_show_open?"open,":"",
                    masscan->output.is_show_closed?"closed,":"",
                    masscan->output.is_show_host?"host,":""
                    );
        }
        return 0;
    }
    for (;;) {
        const char *val2 = value;
        unsigned val2_len = INDEX_OF(val2, ',');
        if (val2_len == 0)
            break;
        if (EQUALSx("open", val2, val2_len))
            masscan->output.is_show_open = 1;
        else if (EQUALSx("closed", val2, val2_len) || EQUALSx("close", val2, val2_len))
            masscan->output.is_show_closed = 1;
        else if (EQUALSx("open", val2, val2_len))
            masscan->output.is_show_host = 1;
        else if (EQUALSx("all",val2,val2_len)) {
            masscan->output.is_show_open = 1;
            masscan->output.is_show_host = 1;
            masscan->output.is_show_closed = 1;
        }
        else {
            LOG(0, "FAIL: unknown 'show' spec: %.*s\n", val2_len, val2);
            exit(1);
        }
        value += val2_len;
        while (*value == ',')
            value++;
    }
    return CONF_OK;
}