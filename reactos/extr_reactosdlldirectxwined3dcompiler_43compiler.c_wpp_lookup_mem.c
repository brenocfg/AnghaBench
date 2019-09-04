#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 TYPE_1__* includes ; 
 int includes_size ; 
 int /*<<< orphan*/  initial_filename ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/ * parent_include ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *wpp_lookup_mem(const char *filename, int type, const char *parent_name,
                            char **include_path, int include_path_count)
{
    /* We don't check for file existence here. We will potentially fail on
     * the following wpp_open_mem(). */
    char *path;
    int i;

    TRACE("Looking for include %s, parent %s.\n", debugstr_a(filename), debugstr_a(parent_name));

    parent_include = NULL;
    if (strcmp(parent_name, initial_filename))
    {
        for(i = 0; i < includes_size; i++)
        {
            if(!strcmp(parent_name, includes[i].name))
            {
                parent_include = includes[i].data;
                break;
            }
        }
        if(parent_include == NULL)
        {
            ERR("Parent include %s missing.\n", debugstr_a(parent_name));
            return NULL;
        }
    }

    path = malloc(strlen(filename) + 1);
    if(path)
        memcpy(path, filename, strlen(filename) + 1);
    return path;
}