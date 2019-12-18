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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

char *alarm_name_with_dim(char *name, size_t namelen, const char *dim, size_t dimlen) {
    char *newname,*move;

    newname = malloc(namelen + dimlen + 2);
    if(newname) {
        move = newname;
        memcpy(move, name, namelen);
        move += namelen;

        *move++ = '_';
        memcpy(move, dim, dimlen);
        move += dimlen;
        *move = '\0';
    } else {
        newname = name;
    }

    return newname;
}