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
 int /*<<< orphan*/  free (char*) ; 
 char* wpp_lookup (char const*,int,char const*) ; 
 void* wpp_open (char*,int) ; 

void *pp_open_include(const char *name, int type, const char *parent_name, char **newpath)
{
    char *path;
    void *fp;

    if (!(path = wpp_lookup(name, type, parent_name))) return NULL;
    fp = wpp_open(path, type);

    if (fp)
    {
        if (newpath) *newpath = path;
        else free( path );
        return fp;
    }
    free( path );
    return NULL;
}