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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 char LIST_SEPARATOR_CHAR ; 
 scalar_t__ RAND_load_file (char*,int) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int loadfiles(char *name)
{
    char *p;
    int last, ret = 1;

    for ( ; ; ) {
        last = 0;
        for (p = name; *p != '\0' && *p != LIST_SEPARATOR_CHAR; p++)
            continue;
        if (*p == '\0')
            last = 1;
        *p = '\0';
        if (RAND_load_file(name, -1) < 0) {
            BIO_printf(bio_err, "Can't load %s into RNG\n", name);
            ERR_print_errors(bio_err);
            ret = 0;
        }
        if (last)
            break;
        name = p + 1;
        if (*name == '\0')
            break;
    }
    return ret;
}