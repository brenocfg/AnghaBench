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
 int SOMAXCONN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int get_backlog_size(void)
{
    int backlog = SOMAXCONN;

#ifdef __linux__
    FILE *somaxconn;

    somaxconn = fopen("/proc/sys/net/core/somaxconn", "re");
    if (somaxconn) {
        int tmp;
        if (fscanf(somaxconn, "%d", &tmp) == 1)
            backlog = tmp;
        fclose(somaxconn);
    }
#endif

    return backlog;
}