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
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 unsigned int procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,size_t,int) ; 
 int procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int str2i (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int try_get_zram_major_number(procfile *file) {
    size_t i;
    unsigned int lines = procfile_lines(file);
    int id = -1;
    char *name = NULL;
    for (i = 0; i < lines; i++)
    {
        if (procfile_linewords(file, i) < 2)
            continue;
        name = procfile_lineword(file, i, 1);
        if (strcmp(name, "zram") == 0)
        {
            id = str2i(procfile_lineword(file, i, 0));
            if (id == 0)
                return -1;
            return id;
        }
    }
    return -1;
}