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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdupz_path_subpath (char const*,char const*) ; 

int check_strdupz_path_subpath() {

    struct strdupz_path_subpath_checks {
        const char *path;
        const char *subpath;
        const char *result;
    } checks[] = {
            { "",                "",            "."                     },
            { "/",               "",            "/"                     },
            { "/etc/netdata",    "",            "/etc/netdata"          },
            { "/etc/netdata///", "",            "/etc/netdata"          },
            { "/etc/netdata///", "health.d",    "/etc/netdata/health.d" },
            { "/etc/netdata///", "///health.d", "/etc/netdata/health.d" },
            { "/etc/netdata",    "///health.d", "/etc/netdata/health.d" },
            { "",                "///health.d", "./health.d"            },
            { "/",               "///health.d", "/health.d"             },

            // terminator
            { NULL, NULL, NULL }
    };

    size_t i;
    for(i = 0; checks[i].result ; i++) {
        char *s = strdupz_path_subpath(checks[i].path, checks[i].subpath);
        fprintf(stderr, "strdupz_path_subpath(\"%s\", \"%s\") = \"%s\": ", checks[i].path, checks[i].subpath, s);
        if(!s || strcmp(s, checks[i].result) != 0) {
            freez(s);
            fprintf(stderr, "FAILED\n");
            return 1;
        }
        else {
            freez(s);
            fprintf(stderr, "OK\n");
        }
    }

    return 0;
}