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
 int /*<<< orphan*/  DEFAULT_SLASH ; 
 int pathlen_without_trailing_slash (char*) ; 
 char* skip_slash (char*) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void walk_down_the_path(char* path_start,
                               char* path_stop,
                               void (*cb)(char* begin,
                                          char* end,
                                          void* data),
                               void* data)
{
    char *pos = path_stop + pathlen_without_trailing_slash(path_start);
    cb(path_stop, pos, data);

    while ((pos = skip_slash(pos))[0]) {
        pos = strchr(pos, DEFAULT_SLASH);
        if (!pos) {
            /* The last token without trailing slash
             */
            cb(path_stop, path_stop + strlen(path_stop), data);
            return;
        }
        cb(path_stop, pos, data);
    }
}