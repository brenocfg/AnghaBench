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
 int /*<<< orphan*/ * ignore_file_list ; 
 int ignore_file_list_cnt ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

signed char is_ignored_file(char *str)
{
int i;
for (i = 0 ; i < ignore_file_list_cnt ; i++)
    if (!strcmp(ignore_file_list[i], str))
        return 1;
return 0;
}