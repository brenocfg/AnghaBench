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
struct TYPE_5__ {TYPE_1__* help; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  valtype; } ;
typedef  TYPE_1__ OPTIONS ;
typedef  TYPE_2__ FUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* OPT_HELP_STR ; 
 char* OPT_MORE_STR ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 TYPE_2__* functions ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void list_options_for_command(const char *command)
{
    const FUNCTION *fp;
    const OPTIONS *o;

    for (fp = functions; fp->name != NULL; fp++)
        if (strcmp(fp->name, command) == 0)
            break;
    if (fp->name == NULL) {
        BIO_printf(bio_err, "Invalid command '%s'; type \"help\" for a list.\n",
                command);
        return;
    }

    if ((o = fp->help) == NULL)
        return;

    for ( ; o->name != NULL; o++) {
        if (o->name == OPT_HELP_STR
                || o->name == OPT_MORE_STR
                || o->name[0] == '\0')
            continue;
        BIO_printf(bio_out, "%s %c\n", o->name, o->valtype);
    }
}