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
struct TYPE_2__ {scalar_t__ strip; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ conf ; 
 char* dir_sep ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* loadfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int cmpfile(const char *str, const char *path, const char *fname)
{
    char filename[1024], *buffer;
    int ret;
    FILE *file;

    sprintf(filename, "%s%c%s", path, dir_sep, fname);
    file = fopen(filename, "rb");
    if (!file) {
        if (conf.strip)
            strcat(filename, ".strip");
        else
            strcat(filename, ".normal");
        file = fopen(filename, "rb");
    }
    if (!file) {
        printf("Error: test result file could not be opened.\n");
        exit(1);
    }

    buffer = loadfile(file);
    if (strcmp(buffer, str) != 0)
        ret = 1;
    else
        ret = 0;
    free(buffer);
    fclose(file);

    return ret;
}