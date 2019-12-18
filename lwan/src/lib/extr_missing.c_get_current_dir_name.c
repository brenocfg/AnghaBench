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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int PATH_MAX ; 
 char* getcwd (char*,int) ; 
 char* strdup (char*) ; 

char *get_current_dir_name(void)
{
    char buffer[PATH_MAX];
    char *ret;

    ret = getcwd(buffer, sizeof(buffer));
    return strdup(ret ? ret : "/");
}