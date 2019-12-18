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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* indexed_filename (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int
output_selftest(void)
{
    char *f;

    f = indexed_filename("foo.bar", 1);
    if (strcmp(f, "foo.01.bar") != 0) {
        fprintf(stderr, "output: failed selftest\n");
        return 1;
    }
    free(f);

    f = indexed_filename("foo.b/ar", 2);
    if (strcmp(f, "foo.b/ar.02") != 0) {
        fprintf(stderr, "output: failed selftest\n");
        return 1;
    }
    free(f);

    f = indexed_filename(".foobar", 3);
    if (strcmp(f, ".03.foobar") != 0) {
        fprintf(stderr, "output: failed selftest\n");
        return 1;
    }
    free(f);

    return 0;
}