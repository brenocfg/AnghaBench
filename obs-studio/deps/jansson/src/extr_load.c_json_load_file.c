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
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * json_loadf (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonp_error_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

json_t *json_load_file(const char *path, size_t flags, json_error_t *error)
{
    json_t *result;
    FILE *fp;

    jsonp_error_init(error, path);

    if (path == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    fp = fopen(path, "rb");
    if(!fp)
    {
        error_set(error, NULL, "unable to open %s: %s",
                  path, strerror(errno));
        return NULL;
    }

    result = json_loadf(fp, flags, error);

    fclose(fp);
    return result;
}