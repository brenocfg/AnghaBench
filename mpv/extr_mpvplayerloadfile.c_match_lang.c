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
 int INT_MAX ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int match_lang(char **langs, char *lang)
{
    for (int idx = 0; langs && langs[idx]; idx++) {
        if (lang && strcasecmp(langs[idx], lang) == 0)
            return INT_MAX - idx;
    }
    return 0;
}