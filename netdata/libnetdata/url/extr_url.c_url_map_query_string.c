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
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int url_map_query_string(char **out, char *url) {
    (void)out;
    (void)url;
    int count = 0;

    //First we try to parse considering that there was not URL encode process
    char *moveme = url;
    char *ptr;

    //We always we have at least one here, so I can set this.
    out[count++] = moveme;
    while(moveme) {
        ptr = strchr((moveme+1), '&');
        if(ptr) {
            out[count++] = ptr;
        }

        moveme = ptr;
    }

    //I could not find any '&', so I am assuming now it is like '%26'
    if (count == 1) {
        moveme = url;
        while(moveme) {
            ptr = strchr((moveme+1), '%');
            if(ptr) {
                char *test = (ptr+1);
                if (!strncmp(test, "3f", 2) || !strncmp(test, "3F", 2)) {
                    out[count++] = ptr;
                }
            }
            moveme = ptr;
        }
    }

    return count;
}