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
 char* INI_STR (char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int
ra_find_name(const char *name) {

    const char *ini_names, *p, *next;
    /* php_printf("Loading redis array with name=[%s]\n", name); */

    ini_names = INI_STR("redis.arrays.names");
    for(p = ini_names; p;) {
        next = strchr(p, ',');
        if(next) {
            if(strncmp(p, name, next - p) == 0) {
                return 1;
            }
        } else {
            if(strcmp(p, name) == 0) {
                return 1;
            }
            break;
        }
        p = next + 1;
    }

    return 0;
}