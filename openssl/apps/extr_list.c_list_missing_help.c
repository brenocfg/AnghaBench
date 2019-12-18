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
struct TYPE_5__ {scalar_t__ func; int /*<<< orphan*/ * name; TYPE_1__* help; } ;
struct TYPE_4__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * helpstr; } ;
typedef  TYPE_1__ OPTIONS ;
typedef  TYPE_2__ FUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  bio_out ; 
 scalar_t__ dgst_main ; 
 TYPE_2__* functions ; 

__attribute__((used)) static void list_missing_help(void)
{
    const FUNCTION *fp;
    const OPTIONS *o;

    for (fp = functions; fp->name != NULL; fp++) {
        if ((o = fp->help) != NULL) {
            /* If there is help, list what flags are not documented. */
            for ( ; o->name != NULL; o++) {
                if (o->helpstr == NULL)
                    BIO_printf(bio_out, "%s %s\n", fp->name, o->name);
            }
        } else if (fp->func != dgst_main) {
            /* If not aliased to the dgst command, */
            BIO_printf(bio_out, "%s *\n", fp->name);
        }
    }
}