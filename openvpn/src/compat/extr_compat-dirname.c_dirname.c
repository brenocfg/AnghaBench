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
 scalar_t__ __memrchr (char*,char,int) ; 
 char* strrchr (char*,char) ; 

char *
dirname(char *path)
{
    static const char dot[] = ".";
    char *last_slash;
    char separator = '/';

    /* Find last '/'.  */
    last_slash = path != NULL ? strrchr(path, '/') : NULL;
    /* If NULL, check for \ instead ... might be Windows a path */
    if (!last_slash)
    {
        last_slash = path != NULL ? strrchr(path, '\\') : NULL;
        separator = last_slash ? '\\' : '/'; /* Change the separator if \ was found */
    }

    if (last_slash != NULL && last_slash != path && last_slash[1] == '\0')
    {
        /* Determine whether all remaining characters are slashes.  */
        char *runp;

        for (runp = last_slash; runp != path; --runp)
        {
            if (runp[-1] != separator)
            {
                break;
            }
        }

        /* The '/' is the last character, we have to look further.  */
        if (runp != path)
        {
            last_slash = (char *) __memrchr(path, separator, runp - path);
        }
    }

    if (last_slash != NULL)
    {
        /* Determine whether all remaining characters are slashes.  */
        char *runp;

        for (runp = last_slash; runp != path; --runp)
        {
            if (runp[-1] != separator)
            {
                break;
            }
        }

        /* Terminate the path.  */
        if (runp == path)
        {
            /* The last slash is the first character in the string.  We have to
             * return "/".  As a special case we have to return "//" if there
             * are exactly two slashes at the beginning of the string.  See
             * XBD 4.10 Path Name Resolution for more information.  */
            if (last_slash == path + 1)
            {
                ++last_slash;
            }
            else
            {
                last_slash = path + 1;
            }
        }
        else
        {
            last_slash = runp;
        }

        last_slash[0] = '\0';
    }
    else
    {
        /* This assignment is ill-designed but the XPG specs require to
         * return a string containing "." in any case no directory part is
         * found and so a static and constant string is required.  */
        path = (char *) dot;
    }

    return path;
}