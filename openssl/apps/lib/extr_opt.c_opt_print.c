#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  start ;
struct TYPE_4__ {char* helpstr; char valtype; scalar_t__* name; } ;
typedef  TYPE_1__ OPTIONS ;

/* Variables and functions */
 int MAX_OPT_HELP_WIDTH ; 
 scalar_t__* OPT_HELP_STR ; 
 scalar_t__* OPT_MORE_STR ; 
 scalar_t__* OPT_SECTION_STR ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  opt_printf_stderr (char const*,...) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__* valtype2param (TYPE_1__ const*) ; 

void opt_print(const OPTIONS *o, int width)
{
    const char* help;
    char start[80 + 1];
    char *p;

        help = o->helpstr ? o->helpstr : "(No additional info)";
        if (o->name == OPT_HELP_STR) {
            opt_printf_stderr(help, prog);
            return;
        }
        if (o->name == OPT_SECTION_STR) {
            opt_printf_stderr("\n");
            opt_printf_stderr(help, prog);
            return;
        }

        /* Pad out prefix */
        memset(start, ' ', sizeof(start) - 1);
        start[sizeof(start) - 1] = '\0';

        if (o->name == OPT_MORE_STR) {
            /* Continuation of previous line; pad and print. */
            start[width] = '\0';
            opt_printf_stderr("%s  %s\n", start, help);
            return;
        }

        /* Build up the "-flag [param]" part. */
        p = start;
        *p++ = ' ';
        *p++ = '-';
        if (o->name[0])
            p += strlen(strcpy(p, o->name));
        else
            *p++ = '*';
        if (o->valtype != '-') {
            *p++ = ' ';
            p += strlen(strcpy(p, valtype2param(o)));
        }
        *p = ' ';
        if ((int)(p - start) >= MAX_OPT_HELP_WIDTH) {
            *p = '\0';
            opt_printf_stderr("%s\n", start);
            memset(start, ' ', sizeof(start));
        }
        start[width] = '\0';
        opt_printf_stderr("%s  %s\n", start, help);
}