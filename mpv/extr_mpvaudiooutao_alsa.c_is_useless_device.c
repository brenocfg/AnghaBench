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
 int MP_ARRAY_SIZE (char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static bool is_useless_device(char *name)
{
    char *crap[] = {"rear", "center_lfe", "side", "pulse", "null", "dsnoop", "hw"};
    for (int i = 0; i < MP_ARRAY_SIZE(crap); i++) {
        int l = strlen(crap[i]);
        if (name && strncmp(name, crap[i], l) == 0 &&
            (!name[l] || name[l] == ':'))
            return true;
    }
    // The standard default entry will achieve exactly the same.
    if (name && strcmp(name, "default") == 0)
        return true;
    return false;
}