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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * platform_fopen (char const*,char*) ; 
 unsigned int platform_getpid () ; 

__attribute__((used)) static void
write_pid(const char *filename)
{
    if (filename)
    {
        unsigned int pid = 0;
        FILE *fp = platform_fopen(filename, "w");
        if (!fp)
        {
            msg(M_ERR, "Open error on pid file %s", filename);
        }

        pid = platform_getpid();
        fprintf(fp, "%u\n", pid);
        if (fclose(fp))
        {
            msg(M_ERR, "Close error on pid file %s", filename);
        }
    }
}