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
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int,char const*,char*,char const*) ; 
 char* strdupz (char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 

char *strdupz_path_subpath(const char *path, const char *subpath) {
    if(unlikely(!path || !*path)) path = ".";
    if(unlikely(!subpath)) subpath = "";

    // skip trailing slashes in path
    size_t len = strlen(path);
    while(len > 0 && path[len - 1] == '/') len--;

    // skip leading slashes in subpath
    while(subpath[0] == '/') subpath++;

    // if the last character in path is / and (there is a subpath or path is now empty)
    // keep the trailing slash in path and remove the additional slash
    char *slash = "/";
    if(path[len] == '/' && (*subpath || len == 0)) {
        slash = "";
        len++;
    }
    else if(!*subpath) {
        // there is no subpath
        // no need for trailing slash
        slash = "";
    }

    char buffer[FILENAME_MAX + 1];
    snprintfz(buffer, FILENAME_MAX, "%.*s%s%s", (int)len, path, slash, subpath);
    return strdupz(buffer);
}